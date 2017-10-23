#pragma once
#include "bmComponent.h"
#include "PhysicsComponentShape.h"
#include <glm\glm.hpp>
#include <vector>

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
        glm::vec2 f = { 0,0 };

        for (auto force : forces) {
            f += force;
        }

        return f.x;
    }

    float getForceY() const {
        glm::vec2 f = { 0,0 };

        for (auto force : forces) {
            f += force;
        }

        return f.y;
    }

    float getMass() const {
        return mass;
    }

    void addForce(float x, float y) {
        forces.push_back({ x, y });
    }

    void resetForce() {
        forces.clear();
    }

private:
    glm::vec2 colliderSize;
    std::vector<glm::vec2> forces;
    float mass = 1.0f;
    PhysicsComponentShape shape;
    bool isStatic;
};
