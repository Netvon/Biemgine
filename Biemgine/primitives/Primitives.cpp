#include "Primitives.h"

#include <cmath>
#include <glm\glm.hpp>

namespace biemgine
{
    Vector& Vector::operator+=(const Vector & other)
    {
        x += other.x; y += other.y; z += other.z;
        return *this;
    }

    Vector Vector::operator+(const Vector & other)
    {
        return { x + other.x, y + other.y, z + other.z };
    }

    Vector & Vector::operator-=(const Vector & other)
    {
        x -= other.x; y -= other.y; z -= other.z;
        return *this;
    }

    Vector Vector::operator-(const Vector & other)
    {
        return { x - other.x, y - other.y, z - other.z };
    }

    Vector & Vector::operator*=(float scalar)
    {
        x *= scalar; y *= scalar; z *= scalar;
        return *this;
    }

    Vector Vector::operator*(float scalar)
    {
        return { x * scalar, y * scalar, z * scalar };
    }

    Vector & Vector::operator/=(float scalar)
    {
        x /= scalar; y /= scalar; z /= scalar;
        return *this;
    }

    Vector Vector::operator/(float scalar)
    {
        return { x / scalar, y / scalar, z / scalar };
    }

    Vector Vector::normalize()
    {
        auto me = *this;
        return me / length();
    }

    float Vector::length()
    {
        return sqrt(x*x + y*y + z*z);
    }

    float Vector::distance(const Vector & b)
    {
        auto temp = *this - b;
        return temp.length();
    }

    Vector & Matrix33::transform(Vector & vector)
    {
        vector.x = (M00 * vector.x) + (M01 * vector.y) + (M02 * vector.z);
        vector.y = (M10 * vector.x) + (M11 * vector.y) + (M12 * vector.z);
        vector.z = (M20 * vector.x) + (M21 * vector.y) + (M22 * vector.z);

        return vector;
    }

    RotMatrix::RotMatrix(double angle)
    {
        // angle = degree;

        const auto rad = angle * (3.1415926535897931 / 180);

        M00 = static_cast<float>(cos(rad));
        M10 = static_cast<float>(sin(rad));
        M20 = 0;

        M01 = static_cast<float>(-sin(rad));
        M11 = static_cast<float>(cos(rad));
        M21 = 0;

        M02 = 0;
        M12 = 0;
        M22 = 1;
    }
}
