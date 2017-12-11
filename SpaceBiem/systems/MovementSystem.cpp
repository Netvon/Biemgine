#include "MovementSystem.h"
#include "..\components\GravityComponent.h"

using biemgine::PositionComponent;
using biemgine::GroundedComponent;
using biemgine::AffectedByGravityComponent;
using biemgine::PhysicsComponent;
using biemgine::Vector;
using biemgine::AnimatedTextureComponent;
using biemgine::TextureFlip;

namespace spacebiem
{
    void MovementSystem::update(const Entity & entity)
    {
        if (!entity.hasComponent("movement"))
            return;

        auto physics = entity.getComponent<PhysicsComponent>("physics");
        auto grounded = entity.getComponent<GroundedComponent>("grounded");

        /*if (!getStateManager()->getInputManager()->isKeyDown("Left")
            && !getStateManager()->getInputManager()->isKeyDown("Right")) {
            physics->setFriction(4.0f);
            return;
        }
        else {
            physics->setFriction(0.0f);
        }*/

        auto texture = entity.getComponent<AnimatedTextureComponent>("texture");

        if (getStateManager()->getInputManager()->isKeyDown("Left") && texture)
            texture->setFlip(TextureFlip::HORIZONTAL);
        if (getStateManager()->getInputManager()->isKeyDown("Right") && texture)
            texture->setFlip(TextureFlip::NONE);

        if (entity.hasComponent("affectedByGravity")
            && entity.hasComponent("grounded")
            && entity.hasComponent("physics"))
        {
            auto position = entity.getComponent<PositionComponent>("position");
            
            auto affected = entity.getComponent<AffectedByGravityComponent>("affectedByGravity");
            

            if (/*!grounded->isGrounded() ||*/ !affected->getIsAffected())
                return;

            Vector centerOfSatellite = {
                position->getX() + physics->getColliderW() / 2.0f,
                position->getY() + physics->getColliderH() / 2.0f
            };

            Vector centerOfGravity = { affected->getFallingTowardsX(), affected->getFallingTowardsY() };
            Vector diff = centerOfGravity - centerOfSatellite;

            constexpr float escapeVelocity = 140.f;
            constexpr float gravityConstant = GravityComponent::getGravityConstant();

            auto movementForce = (physics->getMass() * gravityConstant) * 1.5f;

            auto newVelo = physics->getVelocity().length() + movementForce;

            //printf("%f\n", physics->getFriction());

           /* if (texture != nullptr) {
                if (grounded->isGrounded()) {

                    if (texture->isPausedOrStopped())
                        texture->play();

                    if (physics->getVelocity().length() > 1.0f) {

                        auto veloPercentage = escapeVelocity / physics->getVelocity().length();
                        auto maxSpeed = 32.0f;
                        texture->setPlaybackSpeed(maxSpeed * veloPercentage);
                    }
                    else
                    {
                        texture->stop();
                    }
                }
                else {
                    texture->stop();
                }
            }*/

            //printf("Velo: %f\n", physics->getVelocity().length());

            if (physics->getVelocity().length() > escapeVelocity)
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
