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

	void setX(float x);
	void setY(float y);

	void add(float x, float y) {
		location += glm::vec3(x, y, 0);
	}

private:
	glm::vec3 location;
};

