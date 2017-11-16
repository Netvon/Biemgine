#include "MovementSystem.h"

using biemgine::PositionComponent;
using biemgine::GroundedComponent;
using biemgine::AffectedByGravityComponent;
using biemgine::PhysicsComponent;
using biemgine::Vector;

namespace spacebiem
{
    void MovementSystem::update(const Entity & entity)
    {
        if (!transitionManager->getInputManager()->isKeyDown("Left")
            && !transitionManager->getInputManager()->isKeyDown("Right"))
            return;

        if (entity.hasComponent("affectedByGravity")
            && entity.hasComponent("grounded")
            && entity.hasComponent("physics"))
        {
            auto position = entity.getComponent<PositionComponent*>("position");
            auto grounded = entity.getComponent<GroundedComponent*>("grounded");
            auto affected = entity.getComponent<AffectedByGravityComponent*>("affectedByGravity");
            auto physics = entity.getComponent<PhysicsComponent*>("physics");

            if (!grounded->isGrounded() || !affected->getIsAffected())
                return;

            Vector centerOfSatellite = {
                position->getX() + physics->getColliderW() / 2.0f,
                position->getY() + physics->getColliderH() / 2.0f
            };

            Vector centerOfGravity = { affected->getFallingTowardsX(), affected->getFallingTowardsY() };
            Vector diff = centerOfGravity - centerOfSatellite;

            if (physics->getVelocity().length() > 50)
                return;

            if (transitionManager->getInputManager()->isKeyDown("Left")) {
                Vector left = { -diff.y, diff.x };
                left = left.normalize() * physics->getMass() * 20 * (physics->getMass() * 90);

                physics->addForce("left", left.x, left.y);
            }

            if (transitionManager->getInputManager()->isKeyDown("Right")) {
                Vector right = { diff.y, -diff.x };
                right = right.normalize() * physics->getMass() * 20 * (physics->getMass() * 90);

                physics->addForce("right", right.x, right.y);
            }
        }
    }
}
