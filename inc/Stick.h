#ifndef Stick_h
#define Stick_h

#include "Base.h"

namespace Hanoi
{

    class Stick : public Base
    {
    public:
        Stick(float xCenter, float yCenter, float zCenter,
            float xSize, float ySize, float zSize,
            float* diffColor, float* ambiColor, float* specColor)
            : Base(xCenter, yCenter, zCenter,
                xSize, ySize, zSize,
                specColor, diffColor, ambiColor) { };
        virtual void draw();
    };
}
#endif