#include "Bike.h"

Bike::Bike(float _x, float _y) {
    this->x = _x;
    this->y = _y;


    this->rodas[0] = new Roda(this->x, this->y);
    this->rodas[1] = new Roda(rodas[0]->x+240, rodas[0]->y);

    this->pedal = new Pedal(rodas[0]->x+110, rodas[0]->y+5);

    this->corpoBike[0] = new Vector2(rodas[0]->x, rodas[0]->y); // Roda traseira
    this->corpoBike[1] = new Vector2(pedal->center->x, pedal->center->y); // Pedal
    this->corpoBike[2] = new Vector2(rodas[0]->x + 85, rodas[0]->y + 70); // Parte de cima
    this->corpoBike[3] = new Vector2(rodas[0]->x + 200, rodas[0]->y + 90); // Parte de cima na direita
    this->corpoBike[4] = new Vector2(this->corpoBike[2]->x - 5, this->corpoBike[2]->y + 15); // Banco

    this->corpoPiloto[0] = new Vector2(this->corpoBike[4]->x, this->corpoBike[4]->y); // Quadril
    this->corpoPiloto[1] = new Vector2(this->corpoPiloto[0]->x + 5, this->corpoPiloto[0]->y + 90); // Ombros
    this->corpoPiloto[2] = new Vector2(this->corpoPiloto[1]->x + 45, this->corpoPiloto[1]->y - 40); // Cotovelos
    this->corpoPiloto[3] = new Vector2(this->corpoBike[3]->x - 25, this->corpoBike[3]->y + 40); // Mão
    this->corpoPiloto[4] = new Vector2(this->corpoPiloto[1]->x, this->corpoPiloto[1]->y + 30); // Cabeca

    for (int i = 0; i < 2; i++) {
        this->joelhos[i] = new Vector2(0,0);
    }

}


void Bike::movimenta(float vel, float marcha) {
    giraRodas(vel);
    giraPedais(vel, marcha);
    movePernas();
}

void Bike::draw(int opcao) {
    drawRodas();
    drawPernaEsquerda();
    drawCorpoBike();
    drawPedais();
    drawPernaDireita();
    drawPiloto();
    if(opcao == 1) {
        drawDepuracao();
    }
}


///////////////////////////
// Private
// Movimenta as coisas
void Bike::giraRodas(float vel) {
    for (int i = 0; i < 2; i++) {
        rodas[i]->giraRoda(vel);
    }
}

void Bike::giraPedais(float vel, float marcha) {
    pedal->giraPedais(vel, marcha);
}

void Bike::movePernas() {
    Circle quadril = Circle(corpoPiloto[0]->x, corpoPiloto[0]->y, 60);
    Circle pernaEsquerda = Circle(pedal->pedais[0]->x, pedal->pedais[0]->y, 60);
    Circle pernaDireita = Circle(pedal->pedais[1]->x, pedal->pedais[1]->y, 60);
    std::pair<Point,Point> pedalZero = quadril.intersections(pernaEsquerda);
    std::pair<Point,Point> pedalUm = quadril.intersections(pernaDireita);

    joelhos[0]->x = pedalZero.second.x;
    joelhos[0]->y = pedalZero.second.y;

    joelhos[1]->x = pedalUm.second.x;
    joelhos[1]->y = pedalUm.second.y;
}

//////////////
// Draw

void Bike::drawRodas() {
    for (int i = 0; i < 2; i++) {
        rodas[i]->draw();
    }
}

void Bike::drawPedais() {
    pedal->draw();
}

void Bike::drawCorpoBike() {
    CV::color(0.768, 0.215, 0.705);
    CV::line(corpoBike[0]->x, corpoBike[0]->y, corpoBike[1]->x, corpoBike[1]->y, 6);
    CV::line(corpoBike[0]->x, corpoBike[0]->y, corpoBike[2]->x, corpoBike[2]->y, 6);
    CV::line(corpoBike[1]->x, corpoBike[1]->y, corpoBike[2]->x, corpoBike[2]->y, 6);
    CV::line(corpoBike[1]->x, corpoBike[1]->y, corpoBike[3]->x, corpoBike[3]->y, 6);
    CV::line(corpoBike[2]->x, corpoBike[2]->y, corpoBike[3]->x, corpoBike[3]->y, 6);
    CV::line(corpoBike[2]->x, corpoBike[2]->y, corpoBike[4]->x, corpoBike[4]->y, 6);
    CV::line(corpoBike[3]->x, corpoBike[3]->y, rodas[1]->x, rodas[1]->y, 6);
    CV::line(corpoBike[3]->x, corpoBike[3]->y, corpoBike[3]->x - 10, corpoBike[3]->y + 30, 4);

    // Guidão
    CV::color(0.3,0.3, 0.3);
    CV::line(corpoBike[3]->x - 10, corpoBike[3]->y + 30, corpoBike[3]->x - 10 - 20, corpoBike[3]->y + 30 + 5, 4);

    // Banco
    CV::color(0.3,0.3, 0.3);
    CV::line(corpoBike[4]->x - 10, corpoBike[4]->y, corpoBike[4]->x + 10, corpoBike[4]->y, 8);
}

void Bike::drawPiloto() {
    CV::line(corpoPiloto[0]->x, corpoPiloto[0]->y, corpoPiloto[1]->x, corpoPiloto[1]->y, 10); // Tronco
    CV::line(corpoPiloto[1]->x, corpoPiloto[1]->y, corpoPiloto[2]->x, corpoPiloto[2]->y, 10); // Braço
    CV::line(corpoPiloto[2]->x, corpoPiloto[2]->y, corpoPiloto[3]->x, corpoPiloto[3]->y, 8); // Antebraço
    CV::circleFill(corpoPiloto[3]->x, corpoPiloto[3]->y, 8, 100); // Mao
    CV::circleFill(corpoPiloto[4]->x, corpoPiloto[4]->y, 30, 100); // Cabeca
}

void Bike::drawPernaEsquerda() {
    CV::color(0.1,0.1,0.1);
    CV::line(corpoPiloto[0]->x, corpoPiloto[0]->y, joelhos[0]->x, joelhos[0]->y, 10);
    CV::line(joelhos[0]->x, joelhos[0]->y, pedal->pedais[0]->x, pedal->pedais[0]->y, 10);
}

void Bike::drawPernaDireita() {
    CV::color(0.1,0.1,0.1);
    CV::line(corpoPiloto[0]->x, corpoPiloto[0]->y, joelhos[1]->x, joelhos[1]->y, 10);
    CV::line(joelhos[1]->x, joelhos[1]->y, pedal->pedais[1]->x, pedal->pedais[1]->y, 10);
}

void Bike::drawDepuracao() {
    CV::color(0.8, 0.1, 0.1);
    CV::circle(corpoPiloto[0]->x, corpoPiloto[0]->y, 60, 100);

    for (int i = 0; i < 2; i++) {
        CV::circle(pedal->pedais[i]->x, pedal->pedais[i]->y, 60, 100);
        CV::circleFill(joelhos[i]->x, joelhos[i]->y, 5, 100);
    }

}
