#include "stdafx.h"
#include "bmGravitySystem.h"
#include "bmPlanetGravityComponent.h"
#include "bmAffectedByGravityComponent.h"
#include "bmPositionComponent.h"
#include "bmPhysicsComponent.h"

using namespace glm;

void bmGravitySystem::update(const bmEntity & entity)
{
    if (entity.hasComponent("gravity"))
    {
        gravityPoints.push_back(&entity);
    }
    else if (entity.hasComponent("affectedByGravity") && entity.hasComponent("physics"))
    {
        satalites.push_back(&entity);
    }
}

void bmGravitySystem::after()
{
    for (auto point : gravityPoints) {
        auto gravPosition = point->getComponent<bmPositionComponent*>("position");
        auto gravity = point->getComponent<bmPlanetGravityComponent*>("gravity");

        vec2 centerOfGravity = {
            (gravPosition->getX() + gravity->getX()) + gravity->getWidth() / 2.0f,
            (gravPosition->getY() + gravity->getX()) + gravity->getHeight() / 2.0f
        };

        for (auto& satalite : satalites) {
            auto satPosition = satalite->getComponent<bmPositionComponent*>("position");
            auto satPhysics = satalite->getComponent<bmPhysicsComponent*>("physics");

            vec2 centerOfSatalite = {
                satPosition->getX() + satPhysics->getColliderW() / 2.0f,
                satPosition->getY() + satPhysics->getColliderH() / 2.0f
            };

            auto distance = glm::distance(centerOfGravity, centerOfSatalite);

            if (distance <= gravity->getWidth()) {

                auto force = centerOfGravity - centerOfSatalite;

                force = glm::normalize(force);
                force *= 9000.0f;

                satPhysics->addForce(force.x, force.y);
            }
        }
    }

    gravityPoints.clear();
    satalites.clear();
}
