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
           
            constexpr float escapeVelocity = 140.f;

            if (!grounded->isGrounded() || !affected->getIsAffected())
                return;

            auto physics = entity->getComponent<PhysicsComponent>("physics");

            if (physics->getVelocity().length() > escapeVelocity) {
                continue;
            }

            auto texture = entity->getComponent<AnimatedTextureComponent>("texture");
            auto ai = entity->getComponent<AIComponent>("ai");
            auto position = entity->getComponent<PositionComponent>("position");

            Vector centerOfSatellite = {
                position->getX() + physics->getColliderW() / 2.0f,
                position->getY() + physics->getColliderH() / 2.0f
            };

            Vector centerOfGravity = { affected->getFallingTowardsX(), affected->getFallingTowardsY() };
            Vector diff = centerOfGravity - centerOfSatellite;

            bool playerInRange = false;

            if (ai->getCanFollow()) {
                const Entity * player = findPlayerInRange(entity);

                if (player != nullptr) {
                    playerInRange = true;

                    auto pc = player->getComponent<PositionComponent>("position");
                    ai->setDirection(Direction::LEFT);

                    diff += pc->getLocation() - position->getLocation();
                }
            }

            constexpr float gravityConstant = GravityComponent::getGravityConstant();

            if ((playerInRange && ai->getCanFollow() || ai->getCanWander())) {
                auto movementForce = (physics->getMass() * gravityConstant) * ai->getForce();

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

        ais.clear();
        players.clear();
    }

    const Entity * AIMovementSystem::findPlayerInRange(const Entity * entity) const
    {
        for (auto & player : players) {
            if (entity->distance(*player) < 500.f) {
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
