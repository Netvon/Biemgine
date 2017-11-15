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

        void ground(const Entity * grounded, Entity & ground) const;
        void unground(const Entity * grounded, Entity & ground) const;

        void collide(const Entity * thisEntity, Entity & thatEntity) const;
        void decollide(const Entity * thisEntity, Entity & thatEntity) const;
    };
}
