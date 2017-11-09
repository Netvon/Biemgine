#include "components\UIComponent.h"

namespace biemgine
{
    UIComponent::UIComponent() {}
    UIComponent::~UIComponent() {}

    void UIComponent::setComponentReference(Component * component)
    {
        componentReference = component;
    }

    bool UIComponent::getIsMouseDown() const
    {
        return isMouseDown;
    }

    bool UIComponent::getIsMouseOver() const
    {
        return isMouseOver;
    }
}
