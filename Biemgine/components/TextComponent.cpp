#include "TextComponent.h"

namespace biemgine {
    TextComponent::TextComponent(std::string pText) : text{ pText } {};
    TextComponent::~TextComponent() {}

    const std::string& TextComponent::getText() const {
        return text;
    }

    void TextComponent::setText(const std::string& newText) {
        text = newText;
    }
}
