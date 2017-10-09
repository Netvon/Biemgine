#include "stdafx.h"
#include "bmPhysicsSystem.h"
#include "bmPositionComponent.h"
#include "bmPhysicsComponent.h"
#include "PhysicsComponentShape.h"

#include <random>

bmPhysicsSystem::bmPhysicsSystem()
{
	gravity = new b2Vec2(0, 1);
	world = new b2World(*gravity);
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

	position->setX(body->GetPosition().x);
	position->setY(body->GetPosition().y);

	b2Vec2 force = { static_cast<float>(rand() % 10000 - 5000), static_cast<float>(rand() % 10000 - 5000) };

	std::cout << "x:" << force.x << "y:" << force.y << std::endl;

	body->ApplyForceToCenter(force, true);

	physics->resetForce();
}

void bmPhysicsSystem::onSceneSwitch()
{
	for (auto pair : bodies) {

		/*b2Fixture* f = pair.second->GetFixtureList();
		pair.second->DestroyFixture(f);*/

		world->DestroyBody(pair.second);
		pair.second = nullptr;
	}

	bodies.clear();
}

void bmPhysicsSystem::before()
{
}

void bmPhysicsSystem::after()
{
	world->Step(1.f / 30.0f, 10, 10);
}

void bmPhysicsSystem::destroy()
{
	for (auto pair : bodies) {
		for (b2Fixture* f = pair.second->GetFixtureList(); f; f = f->GetNext())
		{
			pair.second->DestroyFixture(f);
		}

		world->DestroyBody(pair.second);
	}

	delete gravity;
	delete world;
}

b2Body* bmPhysicsSystem::createBody(const bmEntity & entity) {

	auto pc = entity.getComponent<bmPositionComponent*>("position");
	auto physics = entity.getComponent<bmPhysicsComponent*>("physics");

	b2BodyDef newBodyDef;

	if (!physics->getIsStatic())
		newBodyDef.type = b2_dynamicBody;
	else
		newBodyDef.type = b2_staticBody;

	newBodyDef.position.Set(pc->getX(), pc->getY());

	b2Body* body = world->CreateBody(&newBodyDef);
	b2Fixture* fixture = nullptr;

	if (physics->getShape() == RECTANGLE) {

		b2PolygonShape polygonshape;
		polygonshape.SetAsBox(physics->getColliderW() / 2.f, physics->getColliderH() / 2.f, { physics->getColliderW() / 2.f, physics->getColliderH() / 2.f }, 0);

		fixture = body->CreateFixture(&polygonshape, physics->getMass());
	}
	else if (physics->getShape() == CIRCLE) {
		b2CircleShape circleshape;
		circleshape.m_p.Set(0, 0);
		circleshape.m_radius = physics->getColliderW() / 2.0f;

		fixture = body->CreateFixture(&circleshape, physics->getMass());
	}

	fixture->SetRestitution(.5f);

	return body;
}
