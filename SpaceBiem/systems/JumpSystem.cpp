#include "JumpSystem.h"
#include "..\scenes\LevelScene.h"
#include "..\components\GravityComponent.h"

using biemgine::GroundedComponent;
using biemgine::AffectedByGravityComponent;
using biemgine::PositionComponent;
using biemgine::PhysicsComponent;
using biemgine::Vector;

#include <functional>

namespace spacebiem
{
    void JumpSystem::update(const Entity & entity)
    {
        if (!entity.hasComponent("movement"))
            return;

        if (!getStateManager()->getInputManager()->isKeyDown("Space"))
            return;

        if (entity.hasComponent("affectedByGravity")
            && entity.hasComponent("grounded")
            && entity.hasComponent("physics"))
        {
            auto grounded = entity.getComponent<GroundedComponent>("grounded");
            auto affected = entity.getComponent<AffectedByGravityComponent>("affectedByGravity");

            if (!grounded->isGrounded() || !affected->getIsAffected())
                return;

            auto position = entity.getComponent<PositionComponent>("position");
            auto physics = entity.getComponent<PhysicsComponent>("physics");

            Vector centerOfSatellite {
                position->getX() + physics->getColliderW() / 2.0f,
                position->getY() + physics->getColliderH() / 2.0f
            };

            Vector centerOfGravity { affected->getFallingTowardsX(), affected->getFallingTowardsY() };

            Vector diff = (centerOfGravity - centerOfSatellite) * - 1;
            diff = diff.normalize();

            if (physics->getVelocity().length() > 0) {
                diff += physics->getVelocity().normalize();
                diff = diff.normalize();
            }

             auto multiplier = physics->getVelocity().normalize().length() * 2.0f;

             if (multiplier < 1.0f)
                 multiplier = 1.0f;

            constexpr auto gravityConstant = GravityComponent::getGravityConstant();
            auto movementForce = (physics->getMass() * gravityConstant) * (10.0f * multiplier);
            
            diff *= movementForce;

            if (!getStateManager()->getAudioDevice().isPlayingSoundEffect("audio/jump.mp3"))
                getStateManager()->getAudioDevice().playSoundEffect("audio/jump.mp3",0, -1, 64);

            physics->addForce("jump", diff.x, diff.y);
        }
    }
}
