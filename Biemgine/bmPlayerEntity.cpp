#include "stdafx.h"
#include "bmPlayerEntity.h"
#include "bmColorComponent.h"
#include "bmTextureComponent.h"
#include "bmPhysicsComponent.h"


bmPlayerEntity::bmPlayerEntity(int x, int y, int r, int g, int b, int w, int h, float mass)
{
	addComponent("position", new bmPositionComponent(x, y));
	addComponent("color", new bmColorComponent(r, g, b));
	addComponent("texture", new bmTextureComponent("textures/lucas.png", w, h));
	addComponent("physics", new bmPhysicsComponent(static_cast<float>(w), static_cast<float>(h), false, RECTANGLE, mass));
}
