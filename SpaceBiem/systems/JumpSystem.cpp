#include "JumpSystem.h"

namespace spacebiem
{
    void JumpSystem::onAddEntity(Entity & entity)
    {
        if (entity.hasComponent("movement")
            && entity.hasComponent("affectedByGravity")
            && entity.hasComponent("grounded")
            && entity.hasComponent("physics"))
        {
            PlayerEntry playerEntry;
            playerEntry.entity = &entity;
            playerEntry.positionComponent = entity.getComponent<PositionComponent>("position");
            playerEntry.groundedComponent = entity.getComponent<GroundedComponent>("grounded");
            playerEntry.affectedByGravityComponent = entity.getComponent<AffectedByGravityComponent>("affectedByGravity");
            playerEntry.physicsComponent = entity.getComponent<PhysicsComponent>("physics");
            playerEntry.movementComponent = entity.getComponent<MovementComponent>("movement");
            playerEntry.animatedComponent = entity.getComponent<AnimatedTextureComponent>("texture");
            playerEntries.push_back(std::move(playerEntry));
        }	
    }

    void JumpSystem::update()
    {
        if (!getStateManager()->getInputManager()->isKeyDown("Space"))
            return;

        for (const PlayerEntry& player : playerEntries)
        {
            if (!player.groundedComponent->isGrounded() || !player.affectedByGravityComponent->getIsAffected())
                return;

            player.animatedComponent->setCurrentAnimation("jump");
            player.animatedComponent->play();
            player.animatedComponent->setPlaybackSpeed(70.0f);

            Vector centerOfSatellite{
                player.positionComponent->getX() + player.physicsComponent->getColliderW() / 2.0f,
                player.positionComponent->getY() + player.physicsComponent->getColliderH() / 2.0f
            };

            Vector centerOfGravity{player.affectedByGravityComponent->getFallingTowardsX(), player.affectedByGravityComponent->getFallingTowardsY()};

            Vector diff = (centerOfGravity - centerOfSatellite) * -1.0f;
            diff = diff.normalize();

            if (player.physicsComponent->getVelocity().length() > 0.0f)
            {
                diff += player.physicsComponent->getVelocity().normalize();
                diff = diff.normalize();
            }

            auto multiplier = player.physicsComponent->getVelocity().normalize().length() * 2.0f;

			constexpr auto gravityConstant = GravityComponent::getGravityConstant();
			auto movementForce = (player.physicsComponent->getMass() * gravityConstant) * (player.movementComponent->getJumpForce() * multiplier);

            if (multiplier < 1.0f)
                multiplier = 1.0f;

            diff *= movementForce;

            if (!getStateManager()->getAudioDevice().isPlayingSoundEffect("audio/jump.mp3"))
                getStateManager()->getAudioDevice().playSoundEffect("audio/jump.mp3", 0, -1, 64);

            player.physicsComponent->addForce("jump", diff.x, diff.y);
        }
    }
}
