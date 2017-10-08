#pragma once
#include "bmComponent.h"
#include <glm\glm.hpp>

class bmPhysicsComponent :
	public bmComponent
{
public:
	bmPhysicsComponent(float colliderW, float colliderH, bool isStatic, PhysicsComponentShape shape) 
		: colliderSize(colliderW, colliderH), shape(shape), isStatic(isStatic) { };

	const float& getColliderW() const {
		return colliderSize.x;
	}

	const float& getColliderH() const {
		return colliderSize.y;
	}

	PhysicsComponentShape getShape() const {
		return shape;
	}

	bool getIsStatic() const {
		return isStatic;
	}

private:
	glm::vec2 colliderSize;
	PhysicsComponentShape shape;
	bool isStatic;
};

enum PhysicsComponentShape
{
	CIRCLE, RECTANGLE
};