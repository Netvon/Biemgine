#pragma once

#include "Box2D/Dynamics/Contacts/b2Contact.h"
#include "Box2D/Dynamics/b2WorldCallbacks.h"
#include "../../entities/Entity.h"

namespace biemgine
{
    class ContactListener :
        public b2ContactListener
    {
    public:
        ContactListener() {};
        ~ContactListener() {};

        void BeginContact(b2Contact* contact);
        void EndContact(b2Contact* contact);

        Entity* getEntityFromFixture(b2Fixture* fixture);
        void ContactListener::entitySetGrounded(const Entity* entity, const bool grounded) const;
    };
}
