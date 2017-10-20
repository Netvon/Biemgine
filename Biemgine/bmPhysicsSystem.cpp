#include "stdafx.h"
#include "bmPhysicsSystem.h"
#include "bmPositionComponent.h"
#include "bmPhysicsComponent.h"
#include "PhysicsComponentShape.h"
#include "bmGroundedComponent.h"

#include "bmContactListener.h"

#include <random>
#include <math.h>


#define RAD_TO_DEGREE (180.0f / M_PI)
#define DEGREE_TO_RAD (M_PI / 180.0f)

bmPhysicsSystem::bmPhysicsSystem()
{
    gravity = new b2Vec2(0, 0);
    world = new b2World(*gravity);
    world->SetContactListener(new bmContactListener());
}

bmPhysicsSystem::~bmPhysicsSystem()
{
    if (bodies.size() > 0) {

        for (auto pair : bodies) {
            world->DestroyBody(pair.second);
        }
    }

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

    auto physics = entity.getComponent<bmPhysicsComponent*>("physics");
    auto position = entity.getComponent<bmPositionComponent*>("position");

    auto body = bodies.at(entity.getId());

    position->setX(body->GetPosition().x - physics->getColliderW() / 2.f);
    position->setY(body->GetPosition().y - physics->getColliderH() / 2.f);
    position->setRotation(body->GetAngle() * RAD_TO_DEGREE);

    //b2Vec2 force = { static_cast<float>(rand() % 10000 - 5000), static_cast<float>(rand() % 10000 - 5000) };

    b2Vec2 center = { 400, 300 };
    b2Vec2 toCenter = center - body->GetPosition();

    toCenter.Normalize();
    toCenter *= 12000.0f;

    if (entity.hasComponent("grounded")) {
        //auto grounded = entity.getComponent<bmGroundedComponent*>("grounded");

        //if (grounded->isGrounded()) {
        //    //toCenter += -toCenter;

        //    //body->ApplyForceToCenter(toCenter, true);

        //    return;
        //}

        float angle = atan2f(-toCenter.x, toCenter.y);
        body->SetTransform(body->GetPosition(), angle);
    }

    //std::cout << "x:" << force.x << "y:" << force.y << std::endl;

   

    body->ApplyForceToCenter(toCenter, true);


    physics->resetForce();
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
        groundShape.SetAsBox(physics->getColliderW(), physics->getColliderH(), { 0, 0 }, 0);

        b2FixtureDef groundFixtureDef;
        groundFixtureDef.shape = &groundShape;
        groundFixtureDef.isSensor = true;

        b2Fixture* groundFixture = body->CreateFixture(&groundFixtureDef);
    }

    return body;
}
