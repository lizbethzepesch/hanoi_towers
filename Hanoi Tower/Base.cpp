#include "Base.h"

namespace Hanoi {

    Base::Base(float xCenter, float yCenter, float zCenter,
        float xSize, float ySize, float zSize,
        float* diffColor, float* ambiColor, float* specColor)
    {
        CoordsCenter(xCenter, yCenter, zCenter);
        Size(xSize, ySize, zSize);
        Colors(diffColor, ambiColor, specColor);
    }

    void Base::CoordsCenter(float xCenter, float yCenter, float zCenter)
    {
        this->xCenter = xCenter;
        this->yCenter = yCenter;
        this->zCenter = zCenter;
    }

    void Base::Size(float xSize, float ySize, float zSize)
    {
        this->xSize = xSize;
        this->ySize = ySize;
        this->zSize = zSize;
    }

    void Base::Colors(float* diffColor, float* ambiColor, float* specColor)
    {
        this->diffColor = diffColor;
        this->ambiColor = ambiColor;
        this->specColor = specColor;
    }

}