#include "stdafx.h"
#include "bmScoreUIEntity.h"
#include "../components/bmScoreComponent.h"

using std::string;
using biemgine::bmPositionComponent;
using biemgine::bmColorComponent;
using biemgine::bmUIComponent;
using biemgine::bmTextComponent;

namespace spacebiem
{
    bmScoreUIEntity::bmScoreUIEntity(float x, float y, float score, const string& name)
    {
        addComponent("position", new bmPositionComponent(x, y));
        addComponent("color", new bmColorComponent(185, 238, 253));
        addComponent("ui", new bmUIComponent);
        addComponent("score", new bmScoreComponent(score, name));
        addComponent("text", new bmTextComponent);
    }
}
