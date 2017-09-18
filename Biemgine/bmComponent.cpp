#include "stdafx.h"
#include "bmComponent.h"


bmComponent::bmComponent(int x, int y, int width, int height)
{
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
}

bmComponent::~bmComponent()
{
}
