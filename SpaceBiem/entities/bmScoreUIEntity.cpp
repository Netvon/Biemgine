#include "stdafx.h"
#include "bmScoreUIEntity.h"

using namespace biemgine;

#include "../components/bmScoreComponent.h"

bmScoreUIEntity::bmScoreUIEntity(float x, float y, float score, string name)
{
    addComponent("position", new bmPositionComponent(x, y));
    addComponent("color", new bmColorComponent(185, 238, 253));
    addComponent("ui", new bmUIComponent());
    addComponent("score", new bmScoreComponent(score, name));
    addComponent("text", new bmTextComponent());
}
