#include "stdafx.h"
#include "bmJumpSystem.h"
#include "bmPhysicsComponent.h"
#include "bmGroundedComponent.h"
#include "bmAffectedByGravityComponent.h"
#include "bmPositionComponent.h"

#include <glm\glm.hpp>

using namespace glm;

void bmJumpSystem::before()
{
    if (transitionManager->getInputManager()->isKeyDown("Space") && !shouldJump)
        shouldJump = true;
}

void bmJumpSystem::update(const bmEntity & entity)
{
    if (entity.hasComponent("affectedByGravity")
        && entity.hasComponent("grounded")
        && entity.hasComponent("physics")
        && shouldJump)
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

        vec2 diff = centerOfGravity - centerOfGravity;

        float angle = atan2f(-diff.x, diff.y);
        
        physics->addForce(-90000, -90000);

        shouldJump = false;
    }
}
