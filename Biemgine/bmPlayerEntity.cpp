#include "stdafx.h"
#include "bmPlayerEntity.h"
#include "bmColorComponent.h"
#include "bmTextureComponent.h"
#include "bmPhysicsComponent.h"

bmPlayerEntity::bmPlayerEntity(float x, float y, bmColor color, float w, float h, float mass)
{
    addComponent("position", new bmPositionComponent(x, y));
    addComponent("color", new bmColorComponent(color));
    addComponent("texture", new bmTextureComponent("textures/test.png", 0, 0, w, h, 1u));
    addComponent("physics", new bmPhysicsComponent(w, h, false, RECTANGLE, mass));
}
