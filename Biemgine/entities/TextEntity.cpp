#include "TextEntity.h"
#include "..\components\TextComponent.h"
#include "..\components\ScriptComponent.h"

namespace biemgine {

    TextEntity::~TextEntity()
    {
    }

    TextEntity::TextEntity(const string & initialValue, Vector position, bool center, Color color, function<string()> getValue, unsigned int layer)
    {
        addComponent<TextComponent>("text", initialValue, color, 0.0f, 0.0f, true, center);
        addComponent<PositionComponent>("position", position.x, position.y);
        addComponent<ScriptComponent>("script", [this, getValue, color]()
        {
            auto txt = getComponent<TextComponent*>("text");
            txt->setText(getValue(), color);
        });
    }
}
