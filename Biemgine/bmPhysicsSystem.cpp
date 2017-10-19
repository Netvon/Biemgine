#include "stdafx.h"
#include "bmPhysicsSystem.h"
#include "bmPositionComponent.h"
#include "bmPhysicsComponent.h"
#include "PhysicsComponentShape.h"

#include <random>
#include <math.h>



#define RAD_TO_DEGREE (180.0f / M_PI)
#define DEGREE_TO_RAD (M_PI / 180.0f)

bmPhysicsSystem::bmPhysicsSystem()
{
    gravity = new b2Vec2(0, 0);
    world = new b2World(*gravity);
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
    toCenter *= 9000.0f;
    

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

    //newBodyDef.fixedRotation = true;
    newBodyDef.position.Set(pc->getX() + physics->getColliderW() / 2.f, pc->getY() + physics->getColliderH() / 2.f);
    newBodyDef.angle = pc->getRotation() * DEGREE_TO_RAD;

    b2Body* body = world->CreateBody(&newBodyDef);
    b2Fixture* fixture = nullptr;

    if (physics->getShape() == RECTANGLE) {

        b2PolygonShape polygonshape;
        polygonshape.SetAsBox(physics->getColliderW() / 2.f, physics->getColliderH() / 2.f, { 0,0/*physics->getColliderW() / 2.f, physics->getColliderH() / 2.f*/ }, 0);

        fixture = body->CreateFixture(&polygonshape, physics->getMass());
    }
    else if (physics->getShape() == CIRCLE) {
        b2CircleShape circleshape;
        circleshape.m_p.Set(0, 0);
        circleshape.m_radius = physics->getColliderW() / 2.0f;

        fixture = body->CreateFixture(&circleshape, physics->getMass());
    }

    fixture->SetRestitution(1.f);

    return body;
}
