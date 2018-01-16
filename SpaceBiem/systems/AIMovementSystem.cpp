#include "AIMovementSystem.h"

using biemgine::Vector;
using biemgine::RandomGenerator;
using biemgine::Math;

#include "stdafx.h"
#include <math.h>

#include "../components/GravityComponent.h"

namespace spacebiem
{
    void AIMovementSystem::onAddEntity(Entity & entity)
    {
        if (entity.isTag("ai")) {
            auto aiEntry = AIEntry{
                &entity,
                entity.getComponent<PositionComponent>("position"),
                entity.getComponent<GroundedComponent>("grounded"),
                entity.getComponent<AffectedByGravityComponent>("affectedByGravity"),
                entity.getComponent<AnimatedTextureComponent>("animatedTexture"),
                entity.getComponent<PhysicsComponent>("physics"),
                entity.getComponent<AIComponent>("ai"),
            };

            aiEntries.push_back(std::move(aiEntry));
        }

        if (entity.isTag("player")) {
            auto playerEntry = PlayerEntry{
                &entity,
                entity.getComponent<PositionComponent>("position")
            };

            playerEntries.push_back(std::move(playerEntry));
        }
    }

    void AIMovementSystem::update()
    {
        for (const AIEntry & aiEntry : aiEntries) {
            auto grounded = aiEntry.grounded;
            auto affected = aiEntry.affectedByGravity;
            auto texture = aiEntry.animatedTexture;
            auto physics = aiEntry.physics;

            constexpr float escapeVelocity = 140.f;

            if (!grounded->isGrounded() || !affected->getIsAffected())
                continue;

            auto ai = aiEntry.ai;
            auto position = aiEntry.position;

            Vector centerOfSatellite = {
                position->getX() + physics->getColliderW() / 2.0f,
                position->getY() + physics->getColliderH() / 2.0f
            };

            Vector centerOfGravity = { affected->getFallingTowardsX(), affected->getFallingTowardsY() };
            Vector diff = centerOfGravity - centerOfSatellite;

            bool playerInRange = false;

            if (ai->getCanFollow()) {
                const Entity * player = findPlayerInRange(aiEntry.entity);

                if (player != nullptr) {
                    playerInRange = true;

                    auto pc = player->getComponent<PositionComponent>("position");

                    diff += position->getLocation() - pc->getLocation();

                    float angle = atan2(pc->getY() - position->getY(), pc->getX() - position->getX( ));
                    angle = Math::radiansToDegrees(angle);

                    ai->setDirection(angle > 0 ? Direction::RIGHT : Direction::LEFT);
                }
            }

            constexpr float gravityConstant = GravityComponent::getGravityConstant();

            auto movementForce = (physics->getMass() * gravityConstant) * ai->getForce();

            if (physics->getVelocity().length() > escapeVelocity)
                return;

            if ((playerInRange && ai->getCanFollow() || ai->getCanWander())) {
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
    }

    const Entity * AIMovementSystem::findPlayerInRange(const Entity * entity) const
    {
        for (const auto & playerEntry : playerEntries) {
            if (entity->distance(*playerEntry.entity) < 500.f) {
                return playerEntry.entity;
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
