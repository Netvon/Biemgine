#include "stdafx.h"
#include "bmJumpSystem.h"

void bmJumpSystem::update(const bmEntity & entity)
{
    if (!getTransitionManager()->getInputManager()->isKeyDown("Space"))
        return;

    if (entity.hasComponent("affectedByGravity")
        && entity.hasComponent("grounded")
        && entity.hasComponent("physics"))
    {
        auto grounded = entity.getComponent<bmGroundedComponent*>("grounded");
        auto affected = entity.getComponent<bmAffectedByGravityComponent*>("affectedByGravity");

        if (!grounded->isGrounded() || !affected->getIsAffected())
            return;

        auto position = entity.getComponent<bmPositionComponent*>("position");
        auto physics = entity.getComponent<bmPhysicsComponent*>("physics");

        bmVector centerOfSatellite = {
            position->getX() + physics->getColliderW() / 2.0f,
            position->getY() + physics->getColliderH() / 2.0f
        };

        bmVector centerOfGravity = { affected->getFallingTowardsX(), affected->getFallingTowardsY() };

        bmVector diff = centerOfGravity - centerOfSatellite;

        diff *= -1;
        diff = diff.normalize() * 90000.f * 1500.f;
        
        physics->addTimedForce("jump", diff.x, diff.y, 100, true);
    }
}
