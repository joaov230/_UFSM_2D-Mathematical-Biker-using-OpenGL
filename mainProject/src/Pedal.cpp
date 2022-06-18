#include "Pedal.h"

Pedal::Pedal(float _x, float _y) {
    this->center = new Vector2(_x, _y);
    this->pedais[0] = new Vector2 (_x, _y + 30);
    this->pedais[1] = new Vector2 (_x, _y - 30);
}

void Pedal::giraPedais(float vel, float marcha) {
    float xTemp,yTemp, xTemp2, yTemp2;
    double ang = -(marcha/500)*vel;


    for (int i=0; i<2; i++) {
        xTemp = this->pedais[i]->x - this->center->x;
        yTemp = this->pedais[i]->y - this->center->y;

        xTemp2 = xTemp*cos(ang)-yTemp*sin(ang);
        yTemp2 = xTemp*sin(ang)+yTemp*cos(ang);

        this->pedais[i]->x = xTemp2+this->center->x;
        this->pedais[i]->y = yTemp2+this->center->y;
    }
}

void Pedal::draw() {
    CV::color(0,0,0);
    CV::circleFill(center->x, center->y, 8, 100);


    //CV::circleFill(this->x, this->y, this->raio, 100);
    //CV::color(1,1,1);
    //CV::circleFill(this->x, this->y, this->raio-8, 100);

    CV::color(0,0,0);
    CV::line(this->center->x, this->center->y,  this->pedais[0]->x,  this->pedais[0]->y, 2);
    CV::line(this->center->x, this->center->y,  this->pedais[1]->x,  this->pedais[1]->y, 2);

    for (int i = 0; i < 2; i++) {
        CV::line(this->pedais[i]->x - 5, this->pedais[i]->y, this->pedais[i]->x + 5, this->pedais[i]->y, 2);
    }

}
