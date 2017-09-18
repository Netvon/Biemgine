#include "stdafx.h"
#include "bmVector2.h"
#include <math.h>

bmVector2::bmVector2()
{
	x = 0;
	y = 0;
}

float bmVector2::getX()
{
	return x;
}

float bmVector2::getY()
{
	return y;
}

float bmVector2::distance(const bmVector2& other)
{
	return sqrt(pow(other.x - x, 2) + pow(other.y - y, 2));
}

float bmVector2::normalize()
{
	float l = length();
	if (l < FLT_EPSILON) {
		return 0.0f;
	}

	float lInv = 1.0f / l;

	x *= lInv;
	y *= lInv;

	return l;
}

float bmVector2::length()
{
	return sqrtf(x * x + y * y);
}

void bmVector2::operator+=(const bmVector2& other)
{
	x += other.x;
	y += other.y;
}

void bmVector2::operator-=(const bmVector2& other)
{
	x -= other.x;
	y -= other.y;
}

void bmVector2::operator*=(float value)
{
	x *= value;
	y *= value;
}
