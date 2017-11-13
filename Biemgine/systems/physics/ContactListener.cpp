#include "stdafx.h"
#include "ContactListener.h"
#include "..\..\entities\Entity.h"
#include "..\..\components\GroundedComponent.h"

namespace biemgine
{
    void ContactListener::BeginContact(b2Contact* contact)
    {
        if (contact->GetFixtureA()->IsSensor() || contact->GetFixtureB()->IsSensor()) {
            Entity* entity = this->getEntityFromFixture(contact->GetFixtureA());
            Entity* otherEntity = this->getEntityFromFixture(contact->GetFixtureB());

            if (entity->hasComponent("grounded") && otherEntity->hasComponent("ground")) {
                this->entitySetGrounded(entity, true);
            }

            if (entity->hasComponent("ground") && otherEntity->hasComponent("grounded")) {
                this->entitySetGrounded(entity, true);
            }
        }
    }

    void ContactListener::EndContact(b2Contact* contact)
    {
        if (contact->GetFixtureA()->IsSensor() || contact->GetFixtureB()->IsSensor()) {
            Entity* entity = this->getEntityFromFixture(contact->GetFixtureA());
            Entity* otherEntity = this->getEntityFromFixture(contact->GetFixtureB());

            if (entity->hasComponent("grounded") && otherEntity->hasComponent("ground")) {
                this->entitySetGrounded(entity, false);
            }

            if (entity->hasComponent("ground") && otherEntity->hasComponent("grounded")) {
                this->entitySetGrounded(otherEntity, false);
            }
        }
    }

    Entity* ContactListener::getEntityFromFixture(b2Fixture* fixture)
    {
        b2Body* body = fixture->GetBody();

        return static_cast<Entity*>(body->GetUserData());
    }

    void ContactListener::entitySetGrounded(const Entity* entity, const bool grounded) const
    {
        auto gc = entity->getComponent<GroundedComponent*>("grounded");
        gc->setGrounded(grounded);
    }
}