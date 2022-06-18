#ifndef RODA_H
#define RODA_H


#include <stdio.h>
#include <iostream>
#include <vector>
#include <math.h>

#include "Vector2.h"
#include "gl_canvas2d.h"

class Roda
{
    public:
        // Definir as variáveis
        float x;
        float y;
        float raio;
        std::vector<Vector2> aro; // Contém os pontos finais das 6 retas

        Roda(float _x, float _y);

        void giraRoda(float vel);
        void draw();
};

#endif // RODA_H
