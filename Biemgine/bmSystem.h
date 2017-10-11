#pragma once

#include "bmEntity.h"

class bmSystem
{
public:

	virtual ~bmSystem() { };
	virtual void before() = 0;
	virtual void update(const bmEntity& entity) = 0;
	virtual void after() = 0;

	virtual void onSceneSwitch() = 0;
};

