#include "stdafx.h"
#include "bmContactListener.h"
#include "bmEntity.h"
#include "bmGroundedComponent.h"

void bmContactListener::BeginContact(b2Contact* contact)
{
    if (contact->GetFixtureA()->IsSensor() || contact->GetFixtureB()->IsSensor()) {
        bmEntity* entity = this->getEntityFromFixture(contact->GetFixtureA());
        bmEntity* otherEntity = this->getEntityFromFixture(contact->GetFixtureB());

        if (entity->hasComponent("grounded") && otherEntity->hasComponent("ground")) {
            this->entitySetGrounded(entity, true);
        }

        if (entity->hasComponent("ground") && otherEntity->hasComponent("grounded")) {
            this->entitySetGrounded(entity, true);
        }
    }
}

void bmContactListener::EndContact(b2Contact* contact)
{
    if (contact->GetFixtureA()->IsSensor() || contact->GetFixtureB()->IsSensor()) {
        bmEntity* entity = this->getEntityFromFixture(contact->GetFixtureA());
        bmEntity* otherEntity = this->getEntityFromFixture(contact->GetFixtureB());

        if (entity->hasComponent("grounded") && otherEntity->hasComponent("ground")) {
            this->entitySetGrounded(entity, false);
        }

        if (entity->hasComponent("ground") && otherEntity->hasComponent("grounded")) {
            this->entitySetGrounded(otherEntity, false);
        }
    }
}

bmEntity* bmContactListener::getEntityFromFixture(b2Fixture* fixture)
{
    b2Body* body = fixture->GetBody();

    return static_cast<bmEntity*>(body->GetUserData());
}

void bmContactListener::entitySetGrounded(const bmEntity* entity, const bool grounded) const
{
    auto gc = entity->getComponent<bmGroundedComponent*>("grounded");
    gc->setGrounded(grounded);
}
