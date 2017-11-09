#pragma once
#include "dlldef.h"

namespace biemgine
{
    struct BIEMGINE bmColor
    {
        unsigned char r, g, b, a;
    };

    struct BIEMGINE bmVector
    {
        float x = 0, y = 0, z = 0;

        bmVector& operator+=(const bmVector& other);
        bmVector operator+(const bmVector& other);

        bmVector& operator-=(const bmVector& other);
        bmVector operator-(const bmVector& other);

        bmVector& operator*=(float scalar);
        bmVector operator*(float scalar);

        bmVector& operator/=(float scalar);
        bmVector operator/(float scalar);

        bmVector normalize();
        float length();

        float distance(const bmVector&b);
    };
}
