#include "stdafx.h"
#include "bmPlayerEntity.h"
#include "bmColorComponent.h"
#include "bmTextureComponent.h"


bmPlayerEntity::bmPlayerEntity(int x, int y, int r, int g, int b)
{
	addComponent("position", new bmPositionComponent(x, y));
	addComponent("color", new bmColorComponent(r, g, b));
	addComponent("texture", new bmTextureComponent("textures/lucas.png"));
}
