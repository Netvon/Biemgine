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
        else if (entity.hasComponent("affectedByGravity") && entity.hasComponent("physics") )
        {
            if (entity.hasComponent("resourcebonus") && entity.hasComponent("grounded")) {
                auto grounded = entity.getComponent<biemgine::GroundedComponent>("grounded");

                if (grounded->isGrounded())
                    return;
            }

            satellites.push_back(&entity);
        }
    }

    void GravitySystem::after()
    {
        for (auto satellite : satellites) {
            auto satPosition = satellite->getComponent<PositionComponent>("position");
            auto satPhysics = satellite->getComponent<PhysicsComponent>("physics");
            auto satAffected = satellite->getComponent<AffectedByGravityComponent>("affectedByGravity");

            Vector centerOfSatellite {
                satPosition->getX() + satPhysics->getColliderW() / 2.0f,
                satPosition->getY() + satPhysics->getColliderH() / 2.0f
            };

            for (auto point : gravityPoints) {
                auto gravPosition = point->getComponent<PositionComponent>("position");
                auto gravity = point->getComponent<GravityComponent>("gravity");

                Vector centerOfGravity {
                    gravPosition->getX() + gravity->getX() + gravity->getWidth() / 2.0f,
                    gravPosition->getY() + gravity->getY() + gravity->getHeight() / 2.0f
                };

                const auto distance = centerOfGravity.distance(centerOfSatellite);

                if (distance <= gravity->getRadius()) {
                    applyForceAndSetRotation(centerOfGravity, centerOfSatellite, satPhysics, satAffected, satPosition);
                }
            }
        }

        gravityPoints.clear();
        satellites.clear();
    }

    void GravitySystem::applyForceAndSetRotation(Vector& centerOfGravity, Vector& centerOfSatellite, std::shared_ptr<PhysicsComponent> satPhysics, std::shared_ptr<AffectedByGravityComponent> affected, std::shared_ptr<PositionComponent> satPosition)
    {
        auto force = centerOfGravity - centerOfSatellite;

        force = force.normalize();
        force *= satPhysics->getMass() * GravityComponent::getGravityConstant();

        satPhysics->addForce("gravity", force.x, force.y);
        affected->setFallingTowardsX(centerOfGravity.x);
        affected->setFallingTowardsY(centerOfGravity.y);

        float tragetX = centerOfGravity.x - centerOfSatellite.x;
        float tragetY = centerOfGravity.y - centerOfSatellite.y;

        float angle = atan2f(-tragetX, tragetY);
        satPosition->setRotation(angle * (180.0f / 3.14159265358979323846264338327950288f));
    }

    System::required_components GravitySystem::requirements() const
    {
        return {
            System::requirement<PositionComponent>(),
            System::requirement<PhysicsComponent>(),
        };
    }
}
