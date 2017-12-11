#include "AIMovementSystem.h"

using biemgine::PhysicsComponent;
using biemgine::GroundedComponent;
using biemgine::PositionComponent;
using biemgine::AffectedByGravityComponent;
using biemgine::Vector;
using biemgine::RandomGenerator;
using biemgine::AnimatedTextureComponent;

#include "stdafx.h"

using std::cout;

#include "../components/GravityComponent.h"
#include "../components/AIComponent.h"

namespace spacebiem
{
    void AIMovementSystem::update(const Entity & entity)
    {
        if (entity.isTag("ai")) {
            ais.push_back(&entity);
        }
        else if (entity.isTag("player")) {
            players.push_back(&entity);
        }
    }

    void AIMovementSystem::after()
    {
        for (const Entity * entity : ais) {
            auto grounded = entity->getComponent<GroundedComponent>("grounded");
            auto affected = entity->getComponent<AffectedByGravityComponent>("affectedByGravity");
            auto texture = entity->getComponent<AnimatedTextureComponent>("texture");
            auto physics = entity->getComponent<PhysicsComponent>("physics");

            constexpr float escapeVelocity = 140.f;

            if (grounded->isGrounded()) {
                if (texture->isPausedOrStopped()) {
                    texture->play();
                }

                if (physics->getVelocity().length() > 1.0f) {
                    auto veloPercentage = escapeVelocity / physics->getVelocity().length();
                    auto maxSpeed = 32.0f;
                    texture->setPlaybackSpeed(maxSpeed * veloPercentage);
                }
                else {
                    texture->stop();
                }
            }
            else {
                texture->stop();
            }

            if (!grounded->isGrounded() || !affected->getIsAffected())
                return;

            auto ai = entity->getComponent<AIComponent>("ai");
            auto position = entity->getComponent<PositionComponent>("position");

            const Entity * player = findPlayerInRange(entity);

            Vector centerOfSatellite = {
                position->getX() + physics->getColliderW() / 2.0f,
                position->getY() + physics->getColliderH() / 2.0f
            };

            Vector centerOfGravity = { affected->getFallingTowardsX(), affected->getFallingTowardsY() };
            Vector diff = centerOfGravity - centerOfSatellite;

            if (player != nullptr) {
                auto pc = player->getComponent<PositionComponent>("position");
                
                diff += position->getLocation() - pc->getLocation();
            }

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

        ais.clear();
        players.clear();
    }

    const Entity * AIMovementSystem::findPlayerInRange(const Entity * entity) const
    {
        for (const auto * player : players) {
            if (entity->distance(*player) < 500) {
                return player;
            }
        }

        return nullptr;
    }

    Direction AIMovementSystem::computeDirection() const
    {
        return Direction::LEFT;
    }

    float AIMovementSystem::computeForce() const
    {
        return 1.0f;
    }
}
