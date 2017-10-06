#pragma once

#include "bmComponent.h"
#include "bmEntity.h"

#include <map>
#include <iostream>
#include <cassert>

class bmSystem
{
public:

	bmSystem() {};
	virtual void before() = 0;
	virtual void update(const bmEntity& entity) = 0;
	virtual void after() = 0;

	virtual void onSceneSwitch() = 0;
};

