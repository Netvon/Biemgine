#include "TextComponent.h"

namespace biemgine {
    TextComponent::TextComponent(Font pFont, std::string pText, Color pColor, bool center, float pOffsetX, float pOffsetY, bool pVisible, string pTag) :
		font(pFont), text(pText), color(pColor), offsetX(pOffsetX),offsetY(pOffsetY),visible(pVisible), center(center), tag(pTag) {};
    TextComponent::~TextComponent() {}

    const std::string& TextComponent::getText() const {
        return text;
    }

    void TextComponent::setText(std::string newText, Color newColor) {
        text = newText;
        color = newColor;
    }

    const Color& TextComponent::getColor() const {
        return color;
    }

    void TextComponent::setColor(const Color newColor) {
        color = newColor;
    }

    Size TextComponent::getTextSize() const
    {
        return textSize;
    }

    void TextComponent::setTextSize(const Size & pTextSize)
    {
        textSize = pTextSize;
    }

    float TextComponent::getOffsetX() const {
        return offsetX;
    }

    float TextComponent::getOffsetY() const {
        return offsetY;
    }
    bool TextComponent::isVisible() const
    {
        return visible;
    }
    void TextComponent::setVisible(bool pVisible)
    {
        visible = pVisible;
    }

    bool TextComponent::isCenter() const
    {
        return center;
    }

    void TextComponent::setTag(const string & pTag)
    {
        tag = pTag;
    }

    const string & TextComponent::getTag() const
    {
        return tag;
    }
    Font & TextComponent::getFont()
    {
        return font;
    }

}
