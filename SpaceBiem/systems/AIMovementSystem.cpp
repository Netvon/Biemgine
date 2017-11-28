#include "AIMovementSystem.h"

using biemgine::PhysicsComponent;
using biemgine::GroundedComponent;
using biemgine::PositionComponent;
using biemgine::AffectedByGravityComponent;
using biemgine::Vector;
using biemgine::RandomGenerator;

#include "../components/GravityComponent.h"
#include "../components/AIComponent.h"

namespace spacebiem
{
    void AIMovementSystem::update(const Entity & entity)
    {
        if (!entity.hasComponent("ai"))
            return;

        auto ai = entity.getComponent<AIComponent>("ai");

        auto physics = entity.getComponent<PhysicsComponent>("physics");
        auto grounded = entity.getComponent<GroundedComponent>("grounded");
        auto position = entity.getComponent<PositionComponent>("position");
        auto affected = entity.getComponent<AffectedByGravityComponent>("affectedByGravity");

        if (!grounded->isGrounded() || !affected->getIsAffected())
            return;

        Vector centerOfSatellite = {
            position->getX() + physics->getColliderW() / 2.0f,
            position->getY() + physics->getColliderH() / 2.0f
        };

        Vector centerOfGravity = { affected->getFallingTowardsX(), affected->getFallingTowardsY() };
        Vector diff = centerOfGravity - centerOfSatellite;

        constexpr float escapeVelocity = 140.f;
        constexpr float gravityConstant = GravityComponent::getGravityConstant();

        auto movementForce = (physics->getMass() * gravityConstant) * ai->getForce();

        if (physics->getVelocity().length() > escapeVelocity)
            return;

        if (ai->isDirection(Direction::LEFT)) {
            Vector left = { -diff.y, diff.x };
            left = left.normalize() * movementForce;

            physics->addForce("left", left.x, left.y);
        }
        else if (ai->isDirection(Direction::RIGHT)) {
            Vector right = { diff.y, -diff.x };
            right = right.normalize() * movementForce;

            physics->addForce("right", right.x, right.y);
        }
    }
}
