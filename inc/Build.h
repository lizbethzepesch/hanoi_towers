#ifndef Build_h
#define Build_h

namespace Build
{

    extern float diffWhite[];
    extern float ambiWhite[];
    extern float specWhite[];

    extern float diffOrange[];
    extern float ambiOrange[];
    extern float specOrange[];

    extern float diffLightBlue[];
    extern float ambiLightBlue[];
    extern float specLightBlue[];

    extern float diffViolet[];
    extern float ambiViolet[];
    extern float specViolet[];

    const float shininess = 64;

    void parallelepiped(float length, float width, float height);

    void writeText(void* font, const char* text, float x, float y);
}

#endif

