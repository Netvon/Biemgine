#include "stdafx.h"
#include "bmScoreUIEntity.h"
#include "bmPositionComponent.h"
#include "bmUIComponent.h"
#include "bmColorComponent.h"
#include "bmScoreComponent.h"


bmScoreUIEntity::bmScoreUIEntity()
{
    addComponent("position", new bmPositionComponent(0, 0));
    addComponent("color", new bmColorComponent(185, 238, 253));
    addComponent("ui", new bmUIComponent());
    addComponent("score", new bmScoreComponent());
}


bmScoreUIEntity::~bmScoreUIEntity()
{
}
