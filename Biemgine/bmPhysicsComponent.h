#pragma once
#include "bmComponent.h"
#include "PhysicsComponentShape.h"
#include <glm\glm.hpp>



class bmPhysicsComponent :
	public bmComponent
{
public:
	bmPhysicsComponent(float colliderW, float colliderH, bool isStatic, PhysicsComponentShape shape, float mass = 1.0f)
		: colliderSize(colliderW, colliderH), shape(shape), isStatic(isStatic), mass(mass)
	{
		resetForce();
	};

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

	float getForceX() const {
		return force.x;
	}

	float getForceY() const {
		return force.y;
	}

	float getMass() const {
		return mass;
	}

	void addForce(float x, float y) {
		force = { x, y };
	}

	void resetForce() {
		force = { 0.0f, 0.0f };
	}

private:
	glm::vec2 colliderSize;
	glm::vec2 force;
	float mass = 1.0f;
	PhysicsComponentShape shape;
	bool isStatic;
};