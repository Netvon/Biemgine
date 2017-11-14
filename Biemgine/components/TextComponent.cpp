#include "TextComponent.h"

namespace biemgine {
    TextComponent::TextComponent(std::string pText, Color pColor) : text(pText), color(pColor) {};
    TextComponent::~TextComponent() {}

    const std::string& TextComponent::getText() const {
        return text;
    }

    void TextComponent::setText(const std::string& newText, const Color& newColor) {
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

    void TextComponent::setTextSize(const Size & pSize)
    {
        textSize = pSize;
    }
}
