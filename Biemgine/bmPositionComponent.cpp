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
