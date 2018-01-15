#include "GravitySystem.h"
#include "../components/ResourceBonusComponent.h"

using biemgine::PositionComponent;

namespace spacebiem
{
    void GravitySystem::onAddEntity(Entity & entity)
    {
        Entry entry;

        entry.entity = &entity;
        entry.position = entity.getComponent<PositionComponent>("position");
        entry.gravity = entity.getComponent<GravityComponent>("gravity");

        if (entry.gravity == nullptr) {
            entry.grounded = entity.getComponent<GroundedComponent>("grounded");

            if (entry.grounded == nullptr)
                return;

            auto resourcebonus = entity.getComponent<ResourceBonusComponent>("resourcebonus");
            if (resourcebonus != nullptr && entry.grounded->isGrounded())
                return;

            entry.physics = entity.getComponent<PhysicsComponent>("physics");
            entry.affected = entity.getComponent<AffectedByGravityComponent>("affectedByGravity");

            if (entry.physics != nullptr && entry.affected != nullptr) {
                satEntries.push_back(std::move(entry));
            }
        }
        else {
            gravEntries.push_back(std::move(entry));
        }
    }


    void GravitySystem::after()
    {
        for (auto &sat_entry : satEntries) {
            if (!sat_entry.entity->getIsOnScreen())
                continue;

            Vector sat_center{
                sat_entry.position->getX() + sat_entry.physics->getColliderW() / 2.0f,
                sat_entry.position->getY() + sat_entry.physics->getColliderH() / 2.0f
            };

            for (auto &grav_entry : gravEntries) {
                if (!grav_entry.entity->getIsOnScreen())
                    continue;

                Vector grav_center {
                    grav_entry.position->getX() + grav_entry.gravity->getX() + grav_entry.gravity->getWidth() / 2.0f,
                    grav_entry.position->getY() + grav_entry.gravity->getY() + grav_entry.gravity->getHeight() / 2.0f
                };

                const auto distance = grav_center.distance(sat_center);

                if (distance <= grav_entry.gravity->getRadius()) {
                    applyForceAndSetRotation(grav_center, sat_center, sat_entry.physics, sat_entry.affected, sat_entry.position);
                }
            }
        }
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
}
