#pragma once
#include "bmPositionComponent.h"
#include "bmColorComponent.h"

class bmRectangleComponent :
	public bmComponent
{
public:
	bmRectangleComponent(int width, int height, bmColor color) 
		: color({ color.r, color.g, color.b, color.a }), width(width), height(height) { }

	int getWidth() const {
		return width;
	}

	int getHeight() const {
		return height;
	}

	bmColorComponent getColor() const {
		return color;
	}

private:
	int width, height;
	bmColorComponent color;
};