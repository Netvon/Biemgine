#pragma once
#include "../../systems/bmSystem.h"
#include <Box2D/Box2D.h>
#include <vector>
#include "bmContactListener.h"

class bmPhysicsSystem :
    public bmSystem
{
public:
    bmPhysicsSystem();

    ~bmPhysicsSystem();

    void update(const bmEntity& entity) override;
    void onSceneSwitch() override;
    void before() override;

    void after() override;

private:
    b2Vec2* gravity = nullptr;
    b2World* world = nullptr;
    bmContactListener* contactListener = nullptr;

    std::map<int, b2Body*> bodies;

    b2Body* createBody(const bmEntity & entity);
};

