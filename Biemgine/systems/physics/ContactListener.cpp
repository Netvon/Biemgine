#include "stdafx.h"
#include "ContactListener.h"
#include "..\..\entities\Entity.h"
#include "..\..\components\GroundedComponent.h"
#include "..\..\components\CollidableComponent.h"

namespace biemgine
{
    void ContactListener::BeginContact(b2Contact* contact)
    {
        if (contact->GetFixtureA()->IsSensor() || contact->GetFixtureB()->IsSensor()) {
            Entity* entity = this->getEntityFromFixture(contact->GetFixtureA());
            Entity* otherEntity = this->getEntityFromFixture(contact->GetFixtureB());

            if (entity->hasComponent("grounded") && otherEntity->hasComponent("ground")) {
                ground(entity, *otherEntity);
            }

            if (entity->hasComponent("ground") && otherEntity->hasComponent("grounded")) {
                ground(otherEntity, *entity);
            }

            if (entity->hasComponent("collidable") && otherEntity->hasComponent("collidable")) {
                collide(entity, *otherEntity);
                collide(otherEntity, *entity);
            }
        }
    }

    void ContactListener::EndContact(b2Contact* contact)
    {
        if (contact->GetFixtureA()->IsSensor() || contact->GetFixtureB()->IsSensor()) {
            Entity* entity = this->getEntityFromFixture(contact->GetFixtureA());
            Entity* otherEntity = this->getEntityFromFixture(contact->GetFixtureB());

            if (entity->hasComponent("grounded") && otherEntity->hasComponent("ground")) {
                unground(entity, *otherEntity);
            }

            if (entity->hasComponent("ground") && otherEntity->hasComponent("grounded")) {
                unground(otherEntity, *entity);
            }

            if (entity->hasComponent("collidable") && otherEntity->hasComponent("collidable")) {
                decollide(entity, *otherEntity);
                decollide(otherEntity, *entity);
            }
        }
    }

    Entity* ContactListener::getEntityFromFixture(b2Fixture* fixture)
    {
        b2Body* body = fixture->GetBody();

        return static_cast<Entity*>(body->GetUserData());
    }

    void ContactListener::ground(const Entity * grounded, Entity & ground) const
    {
        auto gc = grounded->getComponent<GroundedComponent*>("grounded");
        gc->setGrounded(true, &ground);
    }

    void ContactListener::unground(const Entity * grounded, Entity & ground) const
    {
        auto gc = grounded->getComponent<GroundedComponent*>("grounded");
        gc->setGrounded(false, &ground);
    }

    void ContactListener::collide(const Entity * thisEntity, Entity & thatEntity) const
    {
        auto cc = thisEntity->getComponent<CollidableComponent*>("collidable");
        cc->add(thatEntity);
    }

    void ContactListener::decollide(const Entity * thisEntity, Entity & thatEntity) const
    {
        auto cc = thisEntity->getComponent<CollidableComponent*>("collidable");
        cc->remove(thatEntity);
    }
}
