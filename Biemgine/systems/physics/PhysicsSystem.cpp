#include "stdafx.h"
#include "PhysicsSystem.h"

#include "../../components/PositionComponent.h"
#include "../../components/PhysicsComponent.h"
#include "../../components/PhysicsComponent.h"
#include "../../components/GroundedComponent.h"
#include "../../components/AffectedByGravityComponent.h"

#include <random>
#include <math.h>

namespace biemgine
{
    #define RAD_TO_DEGREE (180.0f / 3.14159265358979323846264338327950288)
    #define DEGREE_TO_RAD (3.14159265358979323846264338327950288 / 180.0f)

    PhysicsSystem::PhysicsSystem()
    {
        contactListener = new ContactListener();
        gravity = new b2Vec2(0, 0);
        world = new b2World(*gravity);
        world->SetContactListener(contactListener);
    }

    PhysicsSystem::~PhysicsSystem()
    {
        world->SetContactListener(nullptr);

        if (bodies.size() > 0) {

            for (auto pair : bodies) {
                world->DestroyBody(pair.second);
            }
        }

        delete contactListener;
        delete gravity;
        delete world;
    }

    void PhysicsSystem::before()
    {
        for (auto pair : bodiesUpdated) {
            bodiesUpdated[pair.first] = false;
        }
    }

    void PhysicsSystem::update(const Entity & entity)
    {
        if (!entity.hasComponent("physics"))
            return;

        if (bodies.find(entity.getId()) == bodies.end()) {
            bodies.insert_or_assign(entity.getId(), createBody(entity));
        }

        auto affectedByGravity = entity.getComponent<AffectedByGravityComponent*>("affectedByGravity");
        auto physics = entity.getComponent<PhysicsComponent*>("physics");
        auto position = entity.getComponent<PositionComponent*>("position");

        auto body = bodies.at(entity.getId());

        position->setX(body->GetPosition().x - physics->getColliderW() / 2.f);
        position->setY(body->GetPosition().y - physics->getColliderH() / 2.f);

        if (entity.hasComponent("grounded")) {
            b2Vec2 ding = {
                affectedByGravity->getFallingTowardsX(),
                affectedByGravity->getFallingTowardsY()
            };

            b2Vec2 target = ding - body->GetPosition();

            target.Normalize();
            target *= 12000.0f;

            float angle = atan2f(-target.x, target.y);
            body->SetTransform(body->GetPosition(), angle);
        }

        position->setRotation(static_cast<float>(body->GetAngle() * RAD_TO_DEGREE));

        body->ApplyForceToCenter({ physics->getForceX() , physics->getForceY() }, true);
        body->ApplyLinearImpulseToCenter({ physics->getImpulseX(), physics->getImpulseY() }, true);

        physics->decreaseTimedForces();

        bodiesUpdated[entity.getId()] = true;
    }

    void PhysicsSystem::after()
    {
        for (auto it = bodiesUpdated.cbegin(); it != bodiesUpdated.cend();)
        {
            if (!(*it).second)
            {
                world->DestroyBody(bodies[(*it).first]);
                bodies.erase(bodies.find((*it).first));
                it = bodiesUpdated.erase(it);
            }
            else
            {
                ++it;
            }
        }

        world->Step(1.f / 30.0f, 6, 2);
    }

    void PhysicsSystem::onSceneSwitch()
    {
        //for (auto pair : *bodies) {

        //    /*b2Fixture* f = pair.second->GetFixtureList();
        //    pair.second->DestroyFixture(f);*/

        //    world->DestroyBody(pair.second);
        //    pair.second = nullptr;
        //}

        //destroy();
    }

    b2Body* PhysicsSystem::createBody(const Entity & entity) {

        auto pc = entity.getComponent<PositionComponent*>("position");
        auto physics = entity.getComponent<PhysicsComponent*>("physics");

        b2BodyDef newBodyDef;

        if (!physics->getIsStatic())
            newBodyDef.type = b2_dynamicBody;
        else
            newBodyDef.type = b2_staticBody;

        if (entity.hasComponent("grounded")) {
            newBodyDef.fixedRotation = true;
        }

        newBodyDef.position.Set(pc->getX() + physics->getColliderW() / 2.f, pc->getY() + physics->getColliderH() / 2.f);
        newBodyDef.angle = static_cast<float>(pc->getRotation() * DEGREE_TO_RAD);
        newBodyDef.linearDamping = 0.2f;

        b2Body* body = world->CreateBody(&newBodyDef);
        body->SetUserData((void*)&entity);
        b2Fixture* fixture = nullptr;

        if (physics->getShape() == RECTANGLE) {
            b2PolygonShape polygonshape;
            polygonshape.SetAsBox(physics->getColliderW() / 2.f, physics->getColliderH() / 2.f, { 0,0/*physics->getColliderW() / 2.f, physics->getColliderH() / 2.f*/ }, 0);

            fixture = body->CreateFixture(&polygonshape, physics->getMass());
        }
        else if (physics->getShape() == CIRCLE) {
            b2CircleShape circleShape;
            circleShape.m_p.Set(0, 0);
            circleShape.m_radius = physics->getColliderW() / 2.0f;

            fixture = body->CreateFixture(&circleShape, physics->getMass());
        }

        fixture->SetRestitution(0.15f);
        fixture->SetFriction(1.f);

        if (entity.hasComponent("grounded")) {
            b2PolygonShape groundShape;
            groundShape.SetAsBox(physics->getColliderW() * 0.5f, physics->getColliderH() * 0.5f, { 0, 0.25f }, 0);

            b2FixtureDef groundFixtureDef;
            groundFixtureDef.shape = &groundShape;
            groundFixtureDef.isSensor = true;

            b2Fixture* groundFixture = body->CreateFixture(&groundFixtureDef);
        }

        return body;
    }
}
