#pragma once

#include "Box2D/Dynamics/Contacts/b2Contact.h"
#include "Box2D/Dynamics/b2WorldCallbacks.h"
#include "../../entities/bmEntity.h"

namespace biemgine {

    class bmContactListener :
        public b2ContactListener
    {
    public:
        bmContactListener() {};
        ~bmContactListener() {};

        void BeginContact(b2Contact* contact);
        void EndContact(b2Contact* contact);

        bmEntity* getEntityFromFixture(b2Fixture* fixture);
        void bmContactListener::entitySetGrounded(const bmEntity* entity, const bool grounded) const;
    };
}
