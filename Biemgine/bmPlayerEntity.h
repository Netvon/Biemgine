#pragma once
#include "bmEntity.h"
#include "bmPositionComponent.h"

class bmPlayerEntity : public bmEntity
{
public:
	bmPlayerEntity(int x, int y, int r, int g, int b, int w = -1, int h = -1, float mass = 1.0f);
};

