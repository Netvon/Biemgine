#pragma once
#include "bmComponent.h"
#include "bmColor.h"

class bmColorComponent :
	public bmComponent
{
public:
	bmColorComponent(int r, int g, int b, int a = 255);
	bmColorComponent(bmColor bmColor);

	int getR() const { return color.r; };
	int getG() const { return color.g; };
	int getB() const { return color.b; };
	int getA() const { return color.a; };

	bmColor getColor() const { return color; }

private:
	bmColor color;
};

