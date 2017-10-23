#include "stdafx.h"
#include "bmScoreUIEntity.h"
#include "bmPositionComponent.h"
#include "bmUIComponent.h"
#include "bmColorComponent.h"
#include "bmScoreComponent.h"
#include "bmTextComponent.h"

bmScoreUIEntity::bmScoreUIEntity(int x, int y, float score)
{
    addComponent("position", new bmPositionComponent(x, y));
    addComponent("color", new bmColorComponent(185, 238, 253));
    addComponent("ui", new bmUIComponent());
    addComponent("score", new bmScoreComponent(score));
    addComponent("text", new bmTextComponent("Score:"));
}

bmScoreUIEntity::~bmScoreUIEntity()
{
}
