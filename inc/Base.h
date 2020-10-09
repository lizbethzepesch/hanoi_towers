#ifndef Base_h//shape
#define Base_h
namespace Hanoi {

    class Base
    {
    private:
        float xCenter, yCenter, zCenter;
        float xSize, ySize, zSize;
        float* diffColor, * ambiColor, * specColor;
    public:
        Base(float xCenter, float yCenter, float zCenter,
            float xSize, float ySize, float zSize,
            float* diffColor, float* ambiColor, float* specColor);
        float  getXCenter() const { return xCenter; }
        float  getYCenter() const { return yCenter; }
        float  getZCenter() const { return zCenter; }
        void   CoordsCenter(float xCenter, float yCenter, float zCenter);

        float  getXSize() const { return xSize; }
        float  getYSize() const { return ySize; }
        float  getZSize() const { return zSize; }
        void   setXCenter(float xCenter) { this->xCenter = xCenter; }
        void   setYCenter(float yCenter) { this->yCenter = yCenter; }
        void   setZCenter(float zCenter) { this->zCenter = zCenter; }

        void   setXSize(float zSize) { this->xSize = xSize; }
        void   setYSize(float zSize) { this->ySize = ySize; }
        void   setZSize(float zSize) { this->zSize = zSize; }
        void   setDiffColor(float* diffColor) { this->diffColor = diffColor; }
        void   setAmbiColor(float* ambiColor) { this->ambiColor = ambiColor; }
        void   setSpecColor(float* specColor) { this->specColor = specColor; }

        void   Size(float xSize, float ySize, float zSize);

        virtual~Base() {};

        float* getDiffColor() const { return diffColor; }
        float* getAmbiColor() const { return ambiColor; }
        float* getSpecColor() const { return specColor; }

        void Colors(float* diffColor, float* ambiColor, float* specColor);
        virtual void draw() = 0;
    };
}
#endif 