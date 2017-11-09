#include "bmPrimitives.h"

#include <cmath>
#include <glm\glm.hpp>

namespace biemgine
{
    bmVector& bmVector::operator+=(const bmVector & other)
    {
        x += other.x; y += other.y; z += other.z;
        return *this;
    }

    bmVector bmVector::operator+(const bmVector & other)
    {
        return { x + other.x, y + other.y, z + other.z };
    }

    bmVector & bmVector::operator-=(const bmVector & other)
    {
        x -= other.x; y -= other.y; z -= other.z;
        return *this;
    }

    bmVector bmVector::operator-(const bmVector & other)
    {
        return { x - other.x, y - other.y, z - other.z };
    }

    bmVector & bmVector::operator*=(float scalar)
    {
        x *= scalar; y *= scalar; z *= scalar;
        return *this;
    }

    bmVector bmVector::operator*(float scalar)
    {
        return { x * scalar, y * scalar, z * scalar };
    }

    bmVector & bmVector::operator/=(float scalar)
    {
        x /= scalar; y /= scalar; z /= scalar;
        return *this;
    }

    bmVector bmVector::operator/(float scalar)
    {
        return { x / scalar, y / scalar, z / scalar };
    }

    bmVector bmVector::normalize()
    {
        auto me = *this;
        return me / length();
    }

    float bmVector::length()
    {
        return sqrt(x*x + y*y + z*z);
    }

    float bmVector::distance(const bmVector & b)
    {
        auto temp = *this - b;
        return temp.length();
    }

    bmVector & bmMatrix33::transform(bmVector & vector)
    {
        vector.x = (M00 * vector.x) + (M01 * vector.y) + (M02 * vector.z);
        vector.y = (M10 * vector.x) + (M11 * vector.y) + (M12 * vector.z);
        vector.z = (M20 * vector.x) + (M21 * vector.y) + (M22 * vector.z);

        return vector;
    }

    bmRotMatrix::bmRotMatrix(double angle)
    {
        // angle = degree;

        const auto rad = angle * (3.1415926535897931 / 180);

        M00 = cos(rad);
        M10 = sin(rad);
        M20 = 0;

        M01 = -sin(rad);
        M11 = cos(rad);
        M21 = 0;

        M02 = 0;
        M12 = 0;
        M22 = 1;
    }
}
