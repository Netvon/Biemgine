#pragma once
#include "bmPositionComponent.h"
#include "bmColorComponent.h"

class bmRectangleComponent :
	public bmComponent
{
public:
	bmRectangleComponent(float width, float height, bmColor color) 
		: color({ color.r, color.g, color.b, color.a }), width(width), height(height) { }

	float getWidth() const {
		return width;
	}

	float getHeight() const {
		return height;
	}

	bmColorComponent getColor() const {
		return color;
	}

private:
	float width, height;
	bmColorComponent color;
};
