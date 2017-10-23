#include "stdafx.h"
#include "bmGravitySystem.h"
#include "bmGravityComponent.h"
#include "bmAffectedByGravityComponent.h"
#include "bmAtmosphereComponent.h"
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
        satellites.push_back(&entity);
    }
}

void bmGravitySystem::after()
{
    for (auto point : gravityPoints) {
        auto atmosphere = point->getComponent<bmAtmosphereComponent*>("atmosphere");
        auto gravPosition = point->getComponent<bmPositionComponent*>("position");
        auto gravity = point->getComponent<bmGravityComponent*>("gravity");

        vec2 centerOfGravity = {
            (gravPosition->getX() + gravity->getX()) + gravity->getWidth() / 2.0f,
            (gravPosition->getY() + gravity->getY()) + gravity->getHeight() / 2.0f
        };

        for (auto& satellite : satellites) {
            auto satPosition = satellite->getComponent<bmPositionComponent*>("position");
            auto satPhysics = satellite->getComponent<bmPhysicsComponent*>("physics");

            vec2 centerOfSatellite = {
                satPosition->getX() + satPhysics->getColliderW() / 2.0f,
                satPosition->getY() + satPhysics->getColliderH() / 2.0f
            };

            auto distance = glm::distance(centerOfGravity, centerOfSatellite);

            if (distance <= atmosphere->getRadius()) {
                auto force = centerOfGravity - centerOfSatellite;

                force = glm::normalize(force);
                force *= 9000.0f;

                satPhysics->addForce(force.x, force.y);
            }
        }
    }

    gravityPoints.clear();
    satellites.clear();
}
