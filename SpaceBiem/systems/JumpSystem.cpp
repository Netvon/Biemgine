#include "JumpSystem.h"

using biemgine::GroundedComponent;
using biemgine::AffectedByGravityComponent;
using biemgine::PositionComponent;
using biemgine::PhysicsComponent;
using biemgine::Vector;

namespace spacebiem
{
    void JumpSystem::update(const Entity & entity)
    {
        if (!entity.hasComponent("movement")) return;

        if (!getTransitionManager()->getInputManager()->isKeyDown("Space"))
            return;

        if (entity.hasComponent("affectedByGravity")
            && entity.hasComponent("grounded")
            && entity.hasComponent("physics"))
        {
            auto grounded = entity.getComponent<GroundedComponent*>("grounded");
            auto affected = entity.getComponent<AffectedByGravityComponent*>("affectedByGravity");

            if (!grounded->isGrounded() || !affected->getIsAffected())
                return;

            auto position = entity.getComponent<PositionComponent*>("position");
            auto physics = entity.getComponent<PhysicsComponent*>("physics");

            Vector centerOfSatellite = {
                position->getX() + physics->getColliderW() / 2.0f,
                position->getY() + physics->getColliderH() / 2.0f
            };

            Vector centerOfGravity = { affected->getFallingTowardsX(), affected->getFallingTowardsY() };

            Vector diff = centerOfGravity - centerOfSatellite;

            diff *= -1;
            diff = diff.normalize() * 90000.f * 1500.f;

            physics->addTimedForce("jump", diff.x, diff.y, 100, true);
        }
    }
}
