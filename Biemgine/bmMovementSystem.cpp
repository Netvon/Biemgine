#include "stdafx.h"
#include "bmPhysicsComponent.h"
#include "bmGroundedComponent.h"
#include "bmAffectedByGravityComponent.h"
#include "bmPositionComponent.h"
#include "bmMovementSystem.h"

#include <glm\glm.hpp>

using namespace glm;

void bmMovementSystem::before()
{
    if (transitionManager->getInputManager()->isKeyDown("Left") && !shouldLeft)
        shouldLeft = true;

    if (transitionManager->getInputManager()->isKeyDown("Right") && !shouldRight)
        shouldRight = true;
}

void bmMovementSystem::update(const bmEntity & entity)
{
    if (entity.hasComponent("affectedByGravity")
        && entity.hasComponent("grounded")
        && entity.hasComponent("physics")
        && (shouldLeft || shouldRight))
    {
        auto position = entity.getComponent<bmPositionComponent*>("position");
        auto grounded = entity.getComponent<bmGroundedComponent*>("grounded");
        auto affected = entity.getComponent<bmAffectedByGravityComponent*>("affectedByGravity");
        auto physics = entity.getComponent<bmPhysicsComponent*>("physics");

        if (!grounded->isGrounded() || !affected->getIsAffected())
            return;

        vec2 centerOfSatellite = {
            position->getX() + physics->getColliderW() / 2.0f,
            position->getY() + physics->getColliderH() / 2.0f
        };

        vec2 centerOfGravity = { affected->getFallingTowardsX(), affected->getFallingTowardsY() };
        vec2 diff = centerOfGravity - centerOfSatellite;

        if (shouldLeft) {
            vec2 left = { -diff.y, diff.x };
            left = glm::normalize(left) * 90000.f * 1500.f;

            physics->addForce("left", left.x, left.y);
            shouldLeft = false;
        }

        if (shouldRight) {
            vec2 right = { diff.y, -diff.x };
            right = glm::normalize(right) * 90000.f * 1500.f;

            physics->addForce("right", right.x, right.y);
            shouldRight = false;
        }
    }
}
