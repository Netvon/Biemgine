#pragma once
#include "bmSystem.h"
#include <vector>
class bmPhysicsSystem :
	public bmSystem
{
public:
	bmPhysicsSystem();

	void update(const bmEntity& entity) override;
	void onSceneSwitch() override;
	void before() override;

	void after() override;

	void destroy() override;

private:
	b2Vec2* gravity = nullptr;
	b2World* world = nullptr;

	std::map<const bmEntity&, b2Body*> bodies;

	b2Body* createBody(const bmEntity & entity);
};

