#include "JumpSystem.h"
#include "../scenes/LevelScene.h"

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
        if (!entity.hasComponent("movement")) return;

        if (!getStateManager()->getInputManager()->isKeyDown("Space"))
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

            Vector centerOfSatellite {
                position->getX() + physics->getColliderW() / 2.0f,
                position->getY() + physics->getColliderH() / 2.0f
            };

            Vector centerOfGravity { affected->getFallingTowardsX(), affected->getFallingTowardsY() };

            Vector diff = centerOfGravity - centerOfSatellite;

            Vector left { -diff.y, diff.x };
            Vector right { diff.y, -diff.x };

            /*if (transitionManager->getInputManager()->isKeyDown("Left")) {
                Vector left = { -diff.y, diff.x };
                left = left.normalize() * physics->getMass() * (90 * 30);

                physics->addTimedForce("left", left.x, left.y, 30);
            }

            if (transitionManager->getInputManager()->isKeyDown("Right")) {
                Vector right = { diff.y, -diff.x };
                right = right.normalize() * physics->getMass() * (90 * 30);

                physics->addTimedForce("right", right.x, right.y, 30);
            }*/

            //diff *= physics->getVelocity();
            diff *= -1;
            diff = diff.normalize();

            if (physics->getVelocity().length() > 0) {
                diff += physics->getVelocity().normalize();
                diff = diff.normalize();
            }

             /**/;

            /*if (getStateManager()->getInputManager()->isKeyDown("Right")) {
                diff += (right * 1.8f);
            }
            else  if (getStateManager()->getInputManager()->isKeyDown("Left")) {
                diff += (left * 1.8f);
            }*/

            //auto diff = [](biemgine::StateManager manager) { manager.navigateTo<LevelScene>(); };

             auto multiplier = physics->getVelocity().normalize().length() * 2.0f;

             if (multiplier < 1.0f)
                 multiplier = 1.0f;

            constexpr auto gravityConstant = 160.f;
            auto movementForce = (physics->getMass() * gravityConstant) * (12.0f * multiplier);
            
            diff *= movementForce;

            physics->addForce("jump", diff.x, diff.y);
        }
    }
}
