#ifndef PEDAL_H
#define PEDAL_H

#include <stdio.h>
#include <iostream>
#include <vector>
#include <math.h>

#include "Vector2.h"
#include "gl_canvas2d.h"

class Pedal
{
    public:
        Vector2 *pedais[2];
        Vector2 *center;

        // X e Y define o centro do pedal
        Pedal(float _x, float _y);

        void giraPedais(float vel, float marcha);
        void draw();

    private:
};

#endif // PEDAL_H
