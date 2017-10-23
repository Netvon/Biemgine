#include "stdafx.h"
#include "bmJumpSystem.h"
#include "bmPhysicsComponent.h"
#include "bmGroundedComponent.h"

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
        auto grounded = entity.getComponent<bmGroundedComponent*>("grounded");

        if (!grounded->isGrounded())
            return;

        auto physics = entity.getComponent<bmPhysicsComponent*>("physics");
        physics->addForce(-90000, -90000);

        shouldJump = false;
    }
}
