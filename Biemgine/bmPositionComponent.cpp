#include "stdafx.h"
#include "bmPositionComponent.h"


float bmPositionComponent::getX() const
{
	return location.x;
}

float bmPositionComponent::getY() const
{
	return location.y;
}

float bmPositionComponent::getZ() const
{
	return location.z;
}

void bmPositionComponent::setX(float x)
{
	location.x = x;
}

void bmPositionComponent::setY(float y)
{
	location.y = y;
}
