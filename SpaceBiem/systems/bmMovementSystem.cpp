#include "bmMovementSystem.h"

using biemgine::bmPositionComponent;
using biemgine::bmGroundedComponent;
using biemgine::bmAffectedByGravityComponent;
using biemgine::bmPhysicsComponent;
using biemgine::bmVector;

namespace spacebiem
{
    void bmMovementSystem::update(const bmEntity & entity)
    {
        if (!transitionManager->getInputManager()->isKeyDown("Left")
            && !transitionManager->getInputManager()->isKeyDown("Right"))
            return;

        if (entity.hasComponent("affectedByGravity")
            && entity.hasComponent("grounded")
            && entity.hasComponent("physics"))
        {
            auto position = entity.getComponent<bmPositionComponent*>("position");
            auto grounded = entity.getComponent<bmGroundedComponent*>("grounded");
            auto affected = entity.getComponent<bmAffectedByGravityComponent*>("affectedByGravity");
            auto physics = entity.getComponent<bmPhysicsComponent*>("physics");

            if (!grounded->isGrounded() || !affected->getIsAffected())
                return;

            bmVector centerOfSatellite = {
                position->getX() + physics->getColliderW() / 2.0f,
                position->getY() + physics->getColliderH() / 2.0f
            };

            bmVector centerOfGravity = { affected->getFallingTowardsX(), affected->getFallingTowardsY() };
            bmVector diff = centerOfGravity - centerOfSatellite;

            if (transitionManager->getInputManager()->isKeyDown("Left")) {
                bmVector left = { -diff.y, diff.x };
                left = left.normalize() * 90000.f * 1500.f;

                physics->addForce("left", left.x, left.y);
            }

            if (transitionManager->getInputManager()->isKeyDown("Right")) {
                bmVector right = { diff.y, -diff.x };
                right = right.normalize() * 90000.f * 1500.f;

                physics->addForce("right", right.x, right.y);
            }
        }
    }
}
