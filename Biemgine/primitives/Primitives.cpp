#include "Primitives.h"

#include <cmath>
#include <tuple>

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

    Vector & Vector::operator*=(const Vector & other)
    {
        x *= other.x; y *= other.y; z *= other.z;

        return *this;
    }

    Vector Vector::operator*(const Vector & other)
    {
        return { x * other.x, y * other.y, z * other.z };
    }

    inline Vector Vector::normalize()
    {
        auto me = *this;
        return me / length();
    }

    inline float Vector::length()
    {
        return sqrt(x*x + y*y + z*z);
    }

    inline float Vector::distance(const Vector & b)
    {
        auto temp = *this - b;
        return temp.length();
    }

    Vector::operator Point()
    {
        return { static_cast<int>(x), static_cast<int>(y), static_cast<int>(z) };
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

    Point::operator Vector()
    {
        return { static_cast<float>(x), static_cast<float>(y), static_cast<float>(z) };
    }

    Color & Color::WithAlpha(unsigned char alpha)
    {
        a = alpha;
        return *this;
    }

    Color & Color::WithRed(unsigned char red)
    {
        r = red;
        return *this;
    }

    Color & Color::WithGreen(unsigned char green)
    {
        g = green;
        return *this;
    }

    Color & Color::WithBlue(unsigned char green)
    {
        g = green;
        return *this;
    }

    bool SizeRect::isEmpty() const
    {
        return (*this) == SizeRect::empty();
    }

    SizeRect SizeRect::empty()
    {
        SizeRect r;
        r.point.x = 0;
        r.point.y = 0;
        r.size.width = -1;
        r.size.height = -1;

        return r;
    }

    bool SizeRect::operator==(const SizeRect & other) const
    {
        return point.x == other.point.x
            && point.y == other.point.y
            && size.width == other.size.width
            && size.height == other.size.height;
    }

    bool SizeRect::operator!=(const SizeRect & other) const
    {
        return point.x != other.point.x
            || point.y != other.point.y
            || size.width != other.size.width
            || size.height != other.size.height;
    }

    bool Font::isEmpty() const
    {
        return size == -1 && name.empty();
    }

    bool Font::operator==(const Font & other) const
    {
        return size == other.size && name == other.name;
    }

    bool Font::operator!=(const Font & other) const
    {
        return size != other.size || name != other.name;;
    }
    bool Font::operator<(const Font & b) const
    {
        return std::tie(name, size) < std::tie(b.name, b.size);
    }

    Font::Font(string pName, int pSize)
        : name(std::move(pName)), size(pSize)
    {

    }
}
