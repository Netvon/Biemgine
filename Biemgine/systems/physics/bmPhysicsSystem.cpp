#include "stdafx.h"
#include "bmPhysicsSystem.h"
#include "../../components/bmPositionComponent.h"
#include "../../components/bmPhysicsComponent.h"
#include "../../components/bmPhysicsComponent.h"
#include "../../components/bmGroundedComponent.h"
#include "../../components/bmAffectedByGravityComponent.h"

#include <random>
#include <math.h>

#define RAD_TO_DEGREE (180.0f / M_PI)
#define DEGREE_TO_RAD (M_PI / 180.0f)

using namespace components;

bmPhysicsSystem::bmPhysicsSystem()
{
    contactListener = new bmContactListener();
    gravity = new b2Vec2(0, 0);
    world = new b2World(*gravity);
    world->SetContactListener(contactListener);
}

bmPhysicsSystem::~bmPhysicsSystem()
{
    if (bodies.size() > 0) {

        for (auto pair : bodies) {
            world->DestroyBody(pair.second);
        }
    }

    delete contactListener;
    delete gravity;
    delete world;
}

void bmPhysicsSystem::update(const bmEntity & entity)
{
    if (!entity.hasComponent("physics"))
        return;

    if (bodies.find(entity.getId()) == bodies.end()) {
        bodies.insert_or_assign(entity.getId(), createBody(entity));
    }

    auto affectedByGravity = entity.getComponent<bmAffectedByGravityComponent*>("affectedByGravity");
    auto physics = entity.getComponent<bmPhysicsComponent*>("physics");
    auto position = entity.getComponent<bmPositionComponent*>("position");

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

    position->setRotation(body->GetAngle() * RAD_TO_DEGREE);

    body->ApplyForceToCenter({ physics->getForceX() , physics->getForceY() }, true);
    body->ApplyLinearImpulseToCenter({ physics->getImpulseX(), physics->getImpulseY() }, true);

    physics->decreaseTimedForces();
}

void bmPhysicsSystem::onSceneSwitch()
{
    //for (auto pair : *bodies) {

    //    /*b2Fixture* f = pair.second->GetFixtureList();
    //    pair.second->DestroyFixture(f);*/

    //    world->DestroyBody(pair.second);
    //    pair.second = nullptr;
    //}

    //destroy();
}

void bmPhysicsSystem::before()
{
}

void bmPhysicsSystem::after()
{
    world->Step(1.f / 30.0f, 6, 2);
}

b2Body* bmPhysicsSystem::createBody(const bmEntity & entity) {

    auto pc = entity.getComponent<bmPositionComponent*>("position");
    auto physics = entity.getComponent<bmPhysicsComponent*>("physics");

    b2BodyDef newBodyDef;

    if (!physics->getIsStatic())
        newBodyDef.type = b2_dynamicBody;
    else
        newBodyDef.type = b2_staticBody;

    if (entity.hasComponent("grounded")) {
        newBodyDef.fixedRotation = true;
    }

    newBodyDef.position.Set(pc->getX() + physics->getColliderW() / 2.f, pc->getY() + physics->getColliderH() / 2.f);
    newBodyDef.angle = pc->getRotation() * DEGREE_TO_RAD;
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
