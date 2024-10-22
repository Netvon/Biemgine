#pragma once
#include "dlldef.h"

#include <string>

using std::string;

namespace biemgine
{
    struct Vector;

    struct BIEMGINE Color
    {
        unsigned char r = 255, g = 255, b = 255, a = 255;

        inline static Color White() {
            return Color();
        }

        inline static Color Black() {
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
        Vector operator-(const Vector& other) const;

        Vector& operator*=(float scalar);
        Vector operator*(float scalar);

        Vector& operator/=(float scalar);
        Vector operator/(float scalar);

        Vector& operator*=(const Vector& other);
        Vector operator*(const Vector& other);

        inline Vector normalize();
        inline float length();

        inline float distance(const Vector&b);

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

    const float PI = 3.14159265358979323846f;

    struct BIEMGINE Math
    {
        static float radiansToDegrees(float radians)
        {
            return radians * 180.f / getPI();
        };

        static float getPI()
        {
            return PI;
        }
    };

    struct BIEMGINE Rect {
        Point topLeft;
        Point topRight;
        Point bottomLeft;
        Point bottomRight;
        bool hasSize;
    };

    struct BIEMGINE SizeRect {
        Point point;
        Size size;

        bool isEmpty() const;
        static SizeRect empty();

        bool operator==(const SizeRect& other) const;
        bool operator!=(const SizeRect& other) const;
    };

    struct BIEMGINE Font {
        string name;
        int size = -1;

        bool isEmpty() const;

        bool operator ==(const Font& other) const;
        bool operator !=(const Font& other) const;

        bool operator < (const Font& b) const;

        Font(string pName, int pSize);
    };
}
