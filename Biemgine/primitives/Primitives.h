#pragma once
#include "dlldef.h"

namespace biemgine
{
    struct Vector;

    struct BIEMGINE Color
    {
        unsigned char r = 255, g = 255, b = 255, a = 255;

        static Color White() {
            return Color();
        }

        static Color Black() {
            return Color{ 0, 0, 0, 255 };
        }

        Color& WithAlpha(unsigned char alpha);
        Color& WithRed(unsigned char red);
        Color& WithGreen(unsigned char green);
        Color& WithBlue(unsigned char green);



    };

    struct BIEMGINE Point {
        int x = 0, y = 0, z = 1;

        operator Vector();
    };

    struct BIEMGINE Size {
        int width = 0, height = 0;
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

        Vector& operator*=(const Vector& other);
        Vector operator*(const Vector& other);

        Vector normalize();
        float length();

        float distance(const Vector&b);

        operator Point();
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

    struct BIEMGINE Rect {
        Point point;
        Size size;
    };
}
