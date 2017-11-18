#include "MovementSystem.h"

using biemgine::PositionComponent;
using biemgine::GroundedComponent;
using biemgine::AffectedByGravityComponent;
using biemgine::PhysicsComponent;
using biemgine::Vector;
using biemgine::TextureComponent;
using biemgine::TextureFlip;

namespace spacebiem
{
    void MovementSystem::update(const Entity & entity)
    {
        if (!entity.hasComponent("movement"))
            return;

        auto physics = entity.getComponent<PhysicsComponent*>("physics");
        auto grounded = entity.getComponent<GroundedComponent*>("grounded");

        if (!getStateManager()->getInputManager()->isKeyDown("Left")
            && !getStateManager()->getInputManager()->isKeyDown("Right"))
            return;

        if (getStateManager()->getInputManager()->isKeyDown("Left") && entity.getComponent<TextureComponent*>("texture")) entity.getComponent<TextureComponent*>("texture")->setFlip(TextureFlip::HORIZONTAL);
        if (getStateManager()->getInputManager()->isKeyDown("Right") && entity.getComponent<TextureComponent*>("texture")) entity.getComponent<TextureComponent*>("texture")->setFlip(TextureFlip::NONE);

        if (entity.hasComponent("affectedByGravity")
            && entity.hasComponent("grounded")
            && entity.hasComponent("physics"))
        {
            auto position = entity.getComponent<PositionComponent*>("position");
            
            auto affected = entity.getComponent<AffectedByGravityComponent*>("affectedByGravity");
            

            if (!grounded->isGrounded() || !affected->getIsAffected())
                return;

            Vector centerOfSatellite = {
                position->getX() + physics->getColliderW() / 2.0f,
                position->getY() + physics->getColliderH() / 2.0f
            };

            Vector centerOfGravity = { affected->getFallingTowardsX(), affected->getFallingTowardsY() };
            Vector diff = centerOfGravity - centerOfSatellite;

            constexpr float terminalVelocity = 100.f;
            constexpr float gravityConstant = 80.f;

            auto movementForce = (physics->getMass() * 2) * (gravityConstant * 2.f);

            auto newVelo = physics->getVelocity().length() + movementForce;

            printf("Velo: %f\n", physics->getVelocity().length());

            if (physics->getVelocity().length() > terminalVelocity)
                return;

            if (getStateManager()->getInputManager()->isKeyDown("Left")) {
                Vector left = { -diff.y, diff.x };
                left = left.normalize() * movementForce;

                physics->addForce("left", left.x, left.y);
            }

            if (getStateManager()->getInputManager()->isKeyDown("Right")) {
                Vector right = { diff.y, -diff.x };
                right = right.normalize() * movementForce;

                physics->addForce("right", right.x, right.y);
            }

            
        }
    }
}
