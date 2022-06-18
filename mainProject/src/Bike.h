#ifndef BIKE_H
#define BIKE_H

#include <stdio.h>
#include <iostream>
#include <vector>
#include <math.h>

#include "Roda.h"
#include "Pedal.h"
#include "Vector2.h"
#include "gl_canvas2d.h"
#include "Circle.cpp"

class Bike
{
    public:
        // X e Y de onde começa a bike, todo o resto será desenhado a partir desse primeiro ponto
        float x;
        float y;
        Roda *rodas[2]; // Contém as duas rodas
        Pedal *pedal; // Contém os dois pedais
        Vector2 *joelhos[2];
        Vector2 *corpoPiloto[5]; // Quadril, ombro, cotovelo, mão e centro da cabeça, em ordem
        Vector2 *corpoBike[5]; // Os 5 pontos estáticos da bike



        Bike(float _x, float _y);

        void movimenta(float vel, float marcha);
        void draw(int opcao);

    private:
        // Ambas chamadas no movimenta();
        void giraRodas(float vel);
        void giraPedais(float vel, float marcha);
        void movePernas();

        void drawPiloto();
        void drawCorpoBike();
        void drawRodas();
        void drawPedais();
        void drawPernaDireita();
        void drawPernaEsquerda();
        void drawDepuracao();
};

#endif // BIKE_H
