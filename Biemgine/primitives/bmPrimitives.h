#pragma once
#include "dlldef.h"

namespace biemgine
{
    struct BIEMGINE bmColor
    {
        unsigned char r, g, b, a;
    };

    struct BIEMGINE bmVector {
        float x = 0, y = 0, z = 1;

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

    struct BIEMGINE bmMatrix33 {
        float M00 = 1.0, M01 = 0.0, M02 = 0.0,
              M10 = 0.0, M11 = 1.0, M12 = 0.0,
              M20 = 0.0, M21 = 0.0, M22 = 1.0;

        bmVector& transform(bmVector& vector);
    };

    struct BIEMGINE bmRotMatrix: public bmMatrix33 {
        bmRotMatrix(double angle);
    };
}
