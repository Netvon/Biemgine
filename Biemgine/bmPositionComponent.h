#pragma once

#include "bmComponent.h"
#include <glm/glm.hpp>

class bmPositionComponent: public bmComponent
{
public:

	bmPositionComponent(float x = 0, float y = 0, float z = 0) : location(x, y, z) {};

	float getX() const;
	float getY() const;
	float getZ() const;

private:
	glm::vec3 location;
};

