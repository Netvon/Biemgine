#include "bmPrimitives.h"

#include <cmath>
#include <glm\glm.hpp>

namespace biemgine {

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
}
