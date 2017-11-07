#pragma once
#include "bmEntity.h"
#include "bmPositionComponent.h"
#include "bmColor.h"

class bmPlayerEntity : public bmEntity
{
public:
    bmPlayerEntity(float x, float y, bmColor color, float w = -1, float h = -1, float mass = 1.0f);
};
