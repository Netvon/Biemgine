#pragma once
#include "dlldef.h"

namespace biemgine
{
    struct BIEMGINE Color
    {
        unsigned char r, g, b, a;
    };

    struct BIEMGINE Vector
    {
        float x = 0, y = 0, z = 1;

        Vector& operator+=(const Vector& other);
        Vector operator+(const Vector& other);

        Vector& operator-=(const Vector& other);
        Vector operator-(const Vector& other);

        Vector& operator*=(float scalar);
        Vector operator*(float scalar);

        Vector& operator/=(float scalar);
        Vector operator/(float scalar);

        Vector normalize();
        float length();

        float distance(const Vector&b);
    };

    struct BIEMGINE Matrix33
    {
        float M00 = 1.0, M01 = 0.0, M02 = 0.0,
              M10 = 0.0, M11 = 1.0, M12 = 0.0,
              M20 = 0.0, M21 = 0.0, M22 = 1.0;

        Vector& transform(Vector& vector);
    };

    struct BIEMGINE RotMatrix: public Matrix33
    {
        RotMatrix(double angle);
    };
}
