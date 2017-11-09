#include "stdafx.h"

#include "../components/bmGravityComponent.h"
#include "bmGravitySystem.h"

namespace spacebiem
{
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

    struct DistanceInfo
    {
        bmVector centerOfGravity;
        bmVector centerOfSatellite;
        bmPhysicsComponent * satPhysics;
    };

    void bmGravitySystem::after()
    {
        for (auto satellite : satellites) {
            auto satPosition = satellite->getComponent<bmPositionComponent*>("position");
            auto satPhysics = satellite->getComponent<bmPhysicsComponent*>("physics");
            auto satAffected = satellite->getComponent<bmAffectedByGravityComponent*>("affectedByGravity");

            bmVector centerOfSatellite = {
                satPosition->getX() + satPhysics->getColliderW() / 2.0f,
                satPosition->getY() + satPhysics->getColliderH() / 2.0f
            };

            map<float, DistanceInfo> distances;
            bool forceApplied = false;

            for (auto point : gravityPoints) {
                auto gravPosition = point->getComponent<bmPositionComponent*>("position");
                auto gravity = point->getComponent<bmGravityComponent*>("gravity");

                bmVector centerOfGravity = {
                    (gravPosition->getX() + gravity->getX()) + gravity->getWidth() / 2.0f,
                    (gravPosition->getY() + gravity->getY()) + gravity->getHeight() / 2.0f
                };

                const auto distance = centerOfGravity.distance(centerOfSatellite);
                distances.insert(pair<float, DistanceInfo>(distance, {
                    centerOfGravity,
                    centerOfSatellite,
                    satPhysics
                }));

                if (distance <= gravity->getRadius()) {
                    applyForce(centerOfGravity, centerOfSatellite, satPhysics, satAffected);
                    forceApplied = true;
                }
            }

            if (!forceApplied) {
                auto distanceInfo = distances.begin()->second;
                applyForce(distanceInfo.centerOfGravity, distanceInfo.centerOfSatellite, distanceInfo.satPhysics, satAffected);
            }
        }

        gravityPoints.clear();
        satellites.clear();
    }

    void bmGravitySystem::applyForce(bmVector centerOfGravity, bmVector centerOfSatellite, bmPhysicsComponent * satPhysics, bmAffectedByGravityComponent* affected)
    {
        auto force = centerOfGravity - centerOfSatellite;

        force = force.normalize();
        force *= 29000.0f;

        satPhysics->addForce("gravity", force.x, force.y);
        affected->setFallingTowardsX(centerOfGravity.x);
        affected->setFallingTowardsY(centerOfGravity.y);
    }
}
