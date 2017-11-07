#include "stdafx.h"
#include "bmPlayerEntity.h"
#include "bmColorComponent.h"
#include "bmGroundedComponent.h"
#include "bmTextureComponent.h"
#include "bmPhysicsComponent.h"
#include "bmAffectedByGravityComponent.h"
#include "bmOxygenComponent.h"
#include "bmScoreComponent.h"

bmPlayerEntity::bmPlayerEntity(float x, float y, bmColor color, float w, float h, float mass)
{
    addComponent("position", new bmPositionComponent(x, y));
    addComponent("color", new bmColorComponent(color));
    addComponent("texture", new bmTextureComponent("textures/player-standing.png", 0, 0, w, h, 5u));
    addComponent("physics", new bmPhysicsComponent(w, h, false, RECTANGLE, mass));
    addComponent("oxygen", new bmOxygenComponent());
    addComponent("grounded", new bmGroundedComponent(false));
    addComponent("score", new bmScoreComponent());
    addComponent("affectedByGravity", new bmAffectedByGravityComponent(true));
}