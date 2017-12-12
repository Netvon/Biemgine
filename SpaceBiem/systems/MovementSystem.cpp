#include "MovementSystem.h"
#include "..\components\GravityComponent.h"

using biemgine::PositionComponent;
using biemgine::GroundedComponent;
using biemgine::AffectedByGravityComponent;
using biemgine::PhysicsComponent;
using biemgine::Vector;
using biemgine::AnimatedTextureComponent;
using biemgine::TextureFlip;
using biemgine::CollidableComponent;

namespace spacebiem
{
    void MovementSystem::update(const Entity & entity)
    {
        if (!entity.hasComponent("movement"))
            return;

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

        auto physics = entity.getComponent<PhysicsComponent>("physics");

        if (!entity.hasComponent("affectedByGravity") || physics == nullptr) {
            return;
        }

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

        constexpr float escapeVelocity = 120.f;
        constexpr float gravityConstant = GravityComponent::getGravityConstant();

        auto movementForce = (physics->getMass() * gravityConstant) * 1.5f;

        auto newVelo = physics->getVelocity().length() + movementForce;

        //printf("%f\n", physics->getFriction());

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

        // bounce away from the AI
        if (entity.hasComponent("collidable")) {
            auto cc = entity.getComponent<CollidableComponent>("collidable");

            for (const auto & collideInfo : cc->getCollisions()) {
                if (collideInfo.entity->isTag("ai")) {
                    physics->addImpulse("bounceback", -physics->getForceX() * 1.1, -physics->getForceY() * 1.1);
                }
            }
        }  
    }

    void MovementSystem::setAnimationSpeed(const float &escapeVelocity, std::shared_ptr<biemgine::PhysicsComponent> &physics, std::shared_ptr<biemgine::AnimatedTextureComponent> &texture)
    {
        auto veloPercentage = escapeVelocity / physics->getVelocity().length();
        constexpr float maxAnimationSpeed = 32.0f;
        texture->setPlaybackSpeed(maxAnimationSpeed * veloPercentage);
    }
}
