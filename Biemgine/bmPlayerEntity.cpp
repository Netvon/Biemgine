#include "stdafx.h"
#include "bmPlayerEntity.h"
#include "bmColorComponent.h"
#include "bmTextureComponent.h"
#include "bmPhysicsComponent.h"
#include "bmOxygenComponent.h"
#include "bmEntityTypeComponent.h"
#include "bmEntityType.h"

bmPlayerEntity::bmPlayerEntity(float x, float y, bmColor color, float w, float h, float mass)
{
    addComponent("position", new bmPositionComponent(x, y));
    addComponent("color", new bmColorComponent(color));
    addComponent("texture", new bmTextureComponent("textures/lucas.png", 0, 0, w, h, 1u));
    addComponent("physics", new bmPhysicsComponent(w, h, false, RECTANGLE, mass));
    addComponent("oxygen", new bmOxygenComponent());
    addComponent("entityType", new bmEntityTypeComponent(PLAYER));
}
