#include "TextEntity.h"
#include "..\components\TextComponent.h"
#include "..\components\ScriptComponent.h"

namespace biemgine {

    TextEntity::~TextEntity()
    {
    }

    TextEntity::TextEntity(Font font, const string & initialValue, Vector position, bool center, Color color, function<string()> getValue, unsigned int layer)
    {
        addComponent<TextComponent>("text", font, initialValue, color, 0.0f, 0.0f, true, center);
        addComponent<PositionComponent>("position", position.x, position.y);
        addComponent<ScriptComponent>("script", [this, getValue, color, txt = getComponent<TextComponent>("text")](float deltaTime)
        {
            txt->setText(getValue(), color);
        });
    }
}
