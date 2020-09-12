
#ifndef Board_h
#define Board_h

#include "Base.h"

namespace Hanoi
{

    // Клас, який відповідає за малювання дошки (поля гри)
    class Board : public Base
    {
    public:
        Board(float xCenter, float yCenter, float zCenter,
            float xSize, float ySize, float zSize,
            float* diffColor, float* ambiColor, float* specColor)
            : Base(xCenter, yCenter, zCenter,
                xSize, ySize, zSize,
                specColor, diffColor, ambiColor) { }
        virtual void draw();
    };

}
#endif
