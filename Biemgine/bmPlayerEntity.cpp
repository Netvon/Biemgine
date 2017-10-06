#include "stdafx.h"
#include "bmPlayerEntity.h"
#include "bmColorComponent.h"


bmPlayerEntity::bmPlayerEntity(int x, int y, int r, int g, int b)
{
	addComponent("position", new bmPositionComponent(x, y));
	addComponent("color", new bmColorComponent(r, g, b));
}
