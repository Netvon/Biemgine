#include "stdafx.h"
#include "bmPhysicsSystem.h"
#include "bmPositionComponent.h"
#include "bmPhysicsComponent.h"

bmPhysicsSystem::bmPhysicsSystem()
{
	gravity = new b2Vec2(0, 0);
	world = new b2World(*gravity);
}

void bmPhysicsSystem::update(const bmEntity & entity)
{
	if (bodies.find(entity) != bodies.end()) {
		bodies.insert_or_assign(entity, createBody(entity));
	}

	
	auto body = bodies.at(entity);

}

void bmPhysicsSystem::after()
{
	world->Step(1.f / 60.f, 6, 2);
}

void bmPhysicsSystem::destroy()
{
	delete gravity;
	delete world;

	for (auto pair : bodies) {
		world->DestroyBody(pair.second);
	}
}

b2Body* bmPhysicsSystem::createBody(const bmEntity & entity) {

	auto pc = entity.getComponent<bmPositionComponent*>("position");
	auto physics = entity.getComponent<bmPhysicsComponent*>("physics");

	b2BodyDef newBodyDef;

	if(!physics->getIsStatic())
		newBodyDef.type = b2_dynamicBody;

	newBodyDef.position.Set(pc->getX(), pc->getY());

	/*b2Shape shape;

	switch (physics->getShape())
	{
	case RECTANGLE:		
		polygonShape.SetAsBox(physics->getColliderW(), physics->getColliderW());

	default:
		break;
	}*/
}
