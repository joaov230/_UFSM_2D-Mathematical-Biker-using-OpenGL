#include "Roda.h"

Roda::Roda(float _x, float _y)
{
    this->raio = 50;
    this->x = _x;
    this->y = _y;


    float xTemp,yTemp, xTemp2, yTemp2;
    double ang = 1.047;
    int posAnterior = 0;

    // Primeira reta
    this->aro.push_back(Vector2(_x, _y+this->raio));

    // Adiciona as outras 5
    for (int i=0; i<5; i++) {
        xTemp = this->aro[i].x - this->x;
        yTemp = this->aro[i].y - this->y;

        xTemp2 = xTemp*cos(ang)-yTemp*sin(ang);
        yTemp2 = xTemp*sin(ang)+yTemp*cos(ang);

        xTemp2 = xTemp2+this->x;
        yTemp2 = yTemp2+this->y;

        this->aro.push_back(Vector2(xTemp2, yTemp2));
    }
}


void Roda::draw() {
    CV::color(0.321,0.321,0.321);
    for (int i=0; i<this->aro.size(); i++) {
        CV::line(this->x, this->y, this->aro[i].x, this->aro[i].y, 5);
    }

    CV::color(0,0,0);
    CV::circle(this->x, this->y, this->raio, 100, 10);


    //CV::circleFill(this->x, this->y, this->raio, 100);
    //CV::color(1,1,1);
    //CV::circleFill(this->x, this->y, this->raio-8, 100);

    CV::color(0.674,0.674, 0.674);
    CV::circleFill(this->x, this->y, 10, 100);
}

void Roda::giraRoda(float vel) {
    float xTemp,yTemp, xTemp2, yTemp2;
    double ang = -0.008*vel;


    for (int i=0; i<6; i++) {
        xTemp = this->aro[i].x - this->x;
        yTemp = this->aro[i].y - this->y;

        xTemp2 = xTemp*cos(ang)-yTemp*sin(ang);
        yTemp2 = xTemp*sin(ang)+yTemp*cos(ang);

        this->aro[i].x = xTemp2+this->x;
        this->aro[i].y = yTemp2+this->y;
    }
}
