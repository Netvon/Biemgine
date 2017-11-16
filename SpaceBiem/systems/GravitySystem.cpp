#include "../components/GravityComponent.h"
#include "GravitySystem.h"

using biemgine::PositionComponent;

namespace spacebiem
{
    void GravitySystem::update(const Entity & entity)
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
        Vector centerOfGravity;
        Vector centerOfSatellite;
        PhysicsComponent * satPhysics;
    };

    void GravitySystem::after()
    {
        for (auto satellite : satellites) {
            auto satPosition = satellite->getComponent<PositionComponent*>("position");
            auto satPhysics = satellite->getComponent<PhysicsComponent*>("physics");
            auto satAffected = satellite->getComponent<AffectedByGravityComponent*>("affectedByGravity");

            Vector centerOfSatellite = {
                satPosition->getX() + satPhysics->getColliderW() / 2.0f,
                satPosition->getY() + satPhysics->getColliderH() / 2.0f
            };

            map<float, DistanceInfo> distances;
            bool forceApplied = false;

            for (auto point : gravityPoints) {
                auto gravPosition = point->getComponent<PositionComponent*>("position");
                auto gravity = point->getComponent<GravityComponent*>("gravity");

                Vector centerOfGravity = {
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

    void GravitySystem::applyForce(Vector centerOfGravity, Vector centerOfSatellite, PhysicsComponent * satPhysics, AffectedByGravityComponent* affected)
    {
        auto force = centerOfGravity - centerOfSatellite;

        force = force.normalize();
        force *= satPhysics->getMass() * 90.0f;

        satPhysics->addForce("gravity", force.x, force.y);
        affected->setFallingTowardsX(centerOfGravity.x);
        affected->setFallingTowardsY(centerOfGravity.y);
    }
}
