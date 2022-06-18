/*********************************************************************
// Canvas para desenho, criada sobre a API OpenGL. Nao eh necessario conhecimentos de OpenGL para usar.
//  Autor: Cesar Tadeu Pozzer
//         05/2020
//
//  Pode ser utilizada para fazer desenhos, animacoes, e jogos simples.
//  Tem tratamento de mouse e teclado
//  Estude o OpenGL antes de tentar compreender o arquivo gl_canvas.cpp
//
//  Versao 2.0
//
// *********************************************************************/

/***********************************
//  Autor do Trabalho: João Vitor Forgearini Beltrame
//  Matrícula: 201713749
//
//  Features:
//    - Acelerar e diminuir a velocidade da bicicleta
//    - Aumentar e diminuir a marcha da bicicleta (os pedais giram mais rápidos ou mais devagar)
//    - Possui cenário que se move com a bicicleta
//      - Marcas no chão (feito com curvas)
//      - Arbustos e nuvens (feitos com circulos simples)
//    - Possui parallax no cenário (objetos distantes se movem mais lentamente que objetos próximos da bicicleta)
//    - Foram usadas curvas bezier para desenhar as marcas no chão (que se movem juntamente com o cenário)
//    - Possui modo Depuracao, ou seja, ao apertar D, o programa mostra os calculos sendo feitos em tempo real (curvas, circulos, etc)
//      assim como informacoes extras: velocidades, marchas e fps
//    - Foi usado intersecção entre circulos para definir a posição dos joelhos do boneco
//    - Controle de FPS (Diminui ou aumenta a animação com base no FPS que o programa roda)
//
// *********************************/


#include <GL/glut.h>
#include <GL/freeglut_ext.h> //callback da wheel do mouse.

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <chrono>
#include <iostream>
#include <cstdlib>
#include <thread>

#include <windows.h>
#include <ctime>
#include <cerrno>

#include "Frames.h"
#include "Roda.h"
#include "Bike.h"
#include "gl_canvas2d.h"

Bike *bicicleta;

float velocidadeBike = 140; //define a velcidade e os pedais giram
float velocidadeBikeTransformada;
float velocidadeCenario = -140; //multiplica o cenário
float velocidadeCenarioTransformada;
float marcha = 200;
float marchaTransformada;
int opcao = 0; // Define se está no modo depuração ou não
int screenWidth = 1000, screenHeight = 500; //largura e altura inicial da tela . Alteram com o redimensionamento de tela.
int mouseX, mouseY; //variaveis globais do mouse para poder exibir dentro da render().

// Calcular
float fps = 0;
Frames *frames;

Vector2 *arbustos[2];
Vector2 *curvaDoChao[4];
Vector2 *circuloNuvem[3];

void desenhaNuvem() {


    CV::color(0.784, 0.8, 0.784);
    for(int i=0;i<3;i++) {
        CV::circleFill(circuloNuvem[i]->x, circuloNuvem[i]->y, 40, 100);
    }

}

void moveNuvem(float vel) {
    for (int i=0; i<3; i++) {
        circuloNuvem[i]->x += vel;
    }
    if (circuloNuvem[0]->x <= -150) {
        for (int i=0; i<3; i++) {
            circuloNuvem[i]->x += screenWidth+300;
        }
    }
    if (circuloNuvem[0]->x >= screenWidth+250) {
        for (int i=0; i<3; i++) {
            circuloNuvem[i]->x -= screenWidth+250;
        }
    }
}

void desenhaCenarioChao () {
    CV::color(0.4, 0.854, 0.980);
    CV::rectFill(0,0,screenWidth,screenHeight);

    desenhaNuvem();

    CV::color(0.22, 0.39, 0.13);
    for (int i=0; i<2; i++) {
        CV::circleFill(arbustos[i]->x, arbustos[i]->y, 50.0, 100.0);
    }
    CV::color(0.396, 0.686, 0.239);
    CV::rectFill(0,0,screenWidth,164);

    CV::color(0.474, 0.847, 0.270);
    Vector2 pontoDeDesenho;
    for (int j = -1; j < 2; j++) {
        for(float t=0; t<1; t+=0.0001) {
            pontoDeDesenho.x = curvaDoChao[0]->x*((1-t)*(1-t)*(1-t)) + curvaDoChao[1]->x*(3*t*((1-t)*(1-t))) + curvaDoChao[2]->x*(3*t*t*(1-t)) + curvaDoChao[3]->x*(t*t*t);
            pontoDeDesenho.y = curvaDoChao[0]->y*((1-t)*(1-t)*(1-t)) + curvaDoChao[1]->y*(3*t*((1-t)*(1-t))) + curvaDoChao[2]->y*(3*t*t*(1-t)) + curvaDoChao[3]->y*(t*t*t);

            pontoDeDesenho.x = pontoDeDesenho.x + screenWidth*j;

            CV::point(pontoDeDesenho);
            CV::line(pontoDeDesenho.x, pontoDeDesenho.y, pontoDeDesenho.x, 0);
        }
    }

}

void moveCenarioChao (float vel) {
    for (int i=0; i<2; i++) {
        arbustos[i]->x += vel;
        if (arbustos[i]->x <= -50) {
            arbustos[i]->x = screenWidth+50;
        }

        if (arbustos[i]->x >= screenWidth+100) {
            arbustos[i]->x = -20;
        }
    }

    for (int i=0; i<4; i++) {
        curvaDoChao[i]->x += vel;
    }
    if (curvaDoChao[3]->x <= 0) {
        for (int i=0; i<4; i++) {
            curvaDoChao[i]->x += screenWidth;
        }
    }
    if (curvaDoChao[0]->x >= screenWidth) {
        for (int i=0; i<4; i++) {
            curvaDoChao[i]->x -= screenWidth;
        }
    }

}

void showInstrucoes() {
    Vector2 posicaoPrint = Vector2(10, 500);
    int i = 15;
    CV::color(0,0,0);
    CV::text(posicaoPrint.x, posicaoPrint.y - 1*i, "[ - Diminui a marcha");
    CV::text(posicaoPrint.x, posicaoPrint.y - 2*i, "] - Aumenta a marcha");
    CV::text(posicaoPrint.x, posicaoPrint.y - 3*i, "<- - Diminui a velocidade");
    CV::text(posicaoPrint.x, posicaoPrint.y - 4*i, "-> - Aumenta a velocidade");
    CV::text(posicaoPrint.x, posicaoPrint.y - 5*i, "D - Modo Depuracao");
}

void desenhaDepuracao() {
    if (opcao == 1) {
        CV::color(0.8, 0.1, 0.1);
        static char ponto[5];
        for (int j = -1; j < 2; j++) {
            for (int i = 0; i < 4; i++) {
                CV::circleFill(curvaDoChao[i]->x + screenWidth*j, curvaDoChao[i]->y, 5, 10);
                sprintf(ponto, "%d", i);
                if (i == 3) {
                    CV::text(curvaDoChao[i]->x + 10 + screenWidth*j, curvaDoChao[i]->y - 25, ponto);
                } else {
                    CV::text(curvaDoChao[i]->x + 10 + screenWidth*j, curvaDoChao[i]->y - 10, ponto);
                }
            }
        }

        for (int i = 0; i < 3; i++) {
            CV::line(curvaDoChao[i]->x, curvaDoChao[i]->y, curvaDoChao[i+1]->x, curvaDoChao[i+1]->y, 1);
        }

        static char velBike[30];
        static char velCenario[30];
        static char marchaText[30];
        static char velBikeTransf[30];
        static char velCenarioTransf[30];
        static char marchaTextTransf[30];
        static char fpsText[30];

        sprintf(velBike, "Velocidade Cenario:  %.0f", velocidadeCenario);
        sprintf(velCenario, "Velocidade Bike:  %.0f", velocidadeBike);
        sprintf(marchaText, "Marcha:  %.0f", marcha);
        sprintf(velBikeTransf, "Vel Cenario Transformada:  %.0f", velocidadeCenarioTransformada);
        sprintf(velCenarioTransf, "Vel Bike Transformada:  %.0f", velocidadeBikeTransformada);
        sprintf(marchaTextTransf, "Marcha Transformada:  %.0f", marchaTransformada);
        sprintf(fpsText, "FPS:  %.0f", fps);

        Vector2 posicaoPrint = Vector2(screenWidth-300, 500);
        int j = 15;
        CV::color(0.1, 0.1, 0.1);
        CV::text(posicaoPrint.x, posicaoPrint.y - 1*j, velBike);
        CV::text(posicaoPrint.x, posicaoPrint.y - 2*j, velCenario);
        CV::text(posicaoPrint.x, posicaoPrint.y - 3*j, marchaText);
        CV::text(posicaoPrint.x, posicaoPrint.y - 4*j, velBikeTransf);
        CV::text(posicaoPrint.x, posicaoPrint.y - 5*j, velCenarioTransf);
        CV::text(posicaoPrint.x, posicaoPrint.y - 6*j, marchaTextTransf);
        CV::text(posicaoPrint.x, posicaoPrint.y - 7*j, fpsText);



    }
}


////////////////////////////////////////////////////
// Canvas

void render()
{
    fps = frames->getFrames();
    velocidadeBikeTransformada = 1/fps * velocidadeBike;
    velocidadeCenarioTransformada = 1/fps * velocidadeCenario;
    marchaTransformada = 1/fps * marcha;

    desenhaCenarioChao();
    showInstrucoes();

    moveCenarioChao(velocidadeCenarioTransformada);
    moveNuvem(velocidadeCenarioTransformada*0.4);

    bicicleta->movimenta(velocidadeBikeTransformada, marchaTransformada);
    bicicleta->draw(opcao);

    desenhaDepuracao();

}

//funcao chamada toda vez que uma tecla for pressionada.
void keyboard(int key)
{
    //printf("\nTecla: %d" , key);

    switch (key) {
        case 202:
            if (velocidadeBike < 1000) {
                velocidadeBike += 20;
                velocidadeCenario -= 20;
            }
            break;
        case 200:
            if (velocidadeBike > 0) {
                velocidadeBike -= 20;
                velocidadeCenario += 20;

            }
            break;
        case 91: // Troca de marcha
            if (marcha > 100) {
                marcha -= 20;
            }
            break;
        case 93:
            if (marcha <= 300) {
                marcha += 20;
            }
            break;
        case 100:
            if (opcao == 0) {
                opcao = 1;
            } else if (opcao == 1) {
                opcao = 0;
            }
            break;
    }


}

//funcao chamada toda vez que uma tecla for liberada
void keyboardUp(int key)
{
    //printf("\nLiberou: %d" , key);


}

//funcao para tratamento de mouse: cliques, movimentos e arrastos
void mouse(int button, int state, int wheel, int direction, int x, int y)
{
    mouseX = x;
    mouseY = y;

    //printf("\nmouse %d %d %d %d %d %d", button, state, wheel, direction,  x, y);


}

void inicializaCenario() {
    arbustos[0] = new Vector2(219, 164);
    arbustos[1] = new Vector2(590, 164);

    // Gera os pontos da curva no chão
    curvaDoChao[0] = new Vector2(0,100);
    curvaDoChao[1] = new Vector2(curvaDoChao[0]->x + (screenWidth/3), curvaDoChao[0]->y + 50);
    curvaDoChao[2] = new Vector2(curvaDoChao[1]->x + (screenWidth/3), curvaDoChao[1]->y - 100);
    curvaDoChao[3] = new Vector2(curvaDoChao[2]->x + (screenWidth/3), curvaDoChao[0]->y);


    circuloNuvem[0] = new Vector2(600, 400);
    circuloNuvem[1] = new Vector2(circuloNuvem[0]->x+60, circuloNuvem[0]->y+5);
    circuloNuvem[2] = new Vector2(circuloNuvem[1]->x-30, circuloNuvem[1]->y+20);

}

int main(void)
{
    // Manda a posição da primeira roda (a da esquerda)
    bicicleta = new Bike((screenWidth/2)-120, 200);

    inicializaCenario();

    frames = new Frames();

    CV::init(&screenWidth, &screenHeight, "Titulo da Janela: Canvas 2D");
    CV::run();
}
