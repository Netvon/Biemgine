#pragma once

#include "bmEntity.h"

class bmSystem
{
public:

	virtual ~bmSystem() { };
    virtual void before() {};
    virtual void before(const float deltaTime) {};
    virtual void update(const bmEntity& entity) {};
    virtual void update(const bmEntity& entity, const float deltaTime) {};
    virtual void after() {};
    virtual void after(const float deltaTime) {};

	virtual void onSceneSwitch() = 0;
};

