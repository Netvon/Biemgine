#include "MovementSystem.h"
#include "..\globals\Cheat.h"

namespace spacebiem
{
    void MovementSystem::onAddEntity(Entity & entity)
    {
        if (!entity.hasComponent("movement")) return;

        MoveEntry moveEntry;
        moveEntry.entity = &entity;
        moveEntry.positionComponent = entity.getComponent<PositionComponent>("position");
        moveEntry.physicsComponent = entity.getComponent<PhysicsComponent>("physics");
        moveEntry.affectedByGravityComponent = entity.getComponent<AffectedByGravityComponent>("affectedByGravity");
        moveEntry.animatedTextureComponent = entity.getComponent<AnimatedTextureComponent>("texture");
        moveEntry.collidableComponent = entity.getComponent<CollidableComponent>("collidable");

        moveEntries.push_back(std::move(moveEntry));

    }

    void MovementSystem::update()
    {
        for (MoveEntry entry : moveEntries)
        {
            if (getStateManager()->getInputManager()->isKeyDown("Left") && entry.animatedTextureComponent)
                entry.animatedTextureComponent->setFlip(TextureFlip::HORIZONTAL);
            if (getStateManager()->getInputManager()->isKeyDown("Right") && entry.animatedTextureComponent)
                entry.animatedTextureComponent->setFlip(TextureFlip::NONE);

            if (!entry.affectedByGravityComponent->getIsAffected())
                return;

            Vector centerOfSatellite = {
                entry.positionComponent->getX() + entry.physicsComponent->getColliderW() / 2.0f,
                entry.positionComponent->getY() + entry.physicsComponent->getColliderH() / 2.0f
            };

            Vector centerOfGravity = {entry.affectedByGravityComponent->getFallingTowardsX(), entry.affectedByGravityComponent->getFallingTowardsY()};
            Vector diff = centerOfGravity - centerOfSatellite;

            constexpr float escapeVelocity = 120.f;
            constexpr float gravityConstant = GravityComponent::getGravityConstant();

            auto movementForce = (entry.physicsComponent->getMass() * gravityConstant) * 1.5f;

            auto newVelo = entry.physicsComponent->getVelocity().length() + movementForce;

            if (entry.physicsComponent->getVelocity().length() > escapeVelocity)
                return; 

            if (getStateManager()->getInputManager()->isKeyDown("Left"))
            {
                Vector left = {-diff.y, diff.x};
                left = left.normalize() * movementForce;

                entry.physicsComponent->addForce("left", left.x, left.y);
            }

            if (getStateManager()->getInputManager()->isKeyDown("Right"))
            {
                Vector right = {diff.y, -diff.x};
                right = right.normalize() * movementForce;

                entry.physicsComponent->addForce("right", right.x, right.y);
            }

            for (const auto & collideInfo : entry.collidableComponent->getCollisions())
            {
                if (collideInfo.entity->isTag("ai") && !Cheat::Instance().isEnabled("ai_bounce"))
                {
                    entry.physicsComponent->addImpulse("bounceback", -entry.physicsComponent->getForceX() * 1.1, -entry.physicsComponent->getForceY() * 1.1);
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
