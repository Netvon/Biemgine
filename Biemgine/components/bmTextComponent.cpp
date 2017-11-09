#include "bmTextComponent.h"

namespace biemgine {
    bmTextComponent::bmTextComponent(std::string pText) : text{ pText } {};
    bmTextComponent::~bmTextComponent() {}

    const std::string& bmTextComponent::getText() const {
        return text;
    }

    void bmTextComponent::setText(const std::string& newText) {
        text = newText;
    }
}
