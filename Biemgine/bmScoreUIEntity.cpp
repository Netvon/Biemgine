#include "stdafx.h"
#include "bmScoreUIEntity.h"
#include "bmPositionComponent.h"
#include "bmUIComponent.h"
#include "bmColorComponent.h"
#include "bmScoreComponent.h"
#include "bmTextComponent.h"

bmScoreUIEntity::bmScoreUIEntity(int x, int y, float score, string name)
{
    addComponent("position", new bmPositionComponent(x, y));
    addComponent("color", new bmColorComponent(185, 238, 253));
    addComponent("ui", new bmUIComponent());
    addComponent("score", new bmScoreComponent(score, name));
    addComponent("text", new bmTextComponent());
}

bmScoreUIEntity::~bmScoreUIEntity()
{
}
