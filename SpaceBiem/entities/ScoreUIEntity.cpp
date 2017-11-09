#include "stdafx.h"
#include "ScoreUIEntity.h"
#include "../components/ScoreComponent.h"

using std::string;
using biemgine::PositionComponent;
using biemgine::ColorComponent;
using biemgine::UIComponent;
using biemgine::TextComponent;

namespace spacebiem
{
    ScoreUIEntity::ScoreUIEntity(float x, float y, float score, const string& name)
    {
        addComponent("position", new PositionComponent(x, y));
        addComponent("color", new ColorComponent(185, 238, 253));
        addComponent("ui", new UIComponent);
        addComponent("score", new ScoreComponent(score, name));
        addComponent("text", new TextComponent);
    }
}
