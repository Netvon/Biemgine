#include "components\UIComponent.h"

namespace biemgine
{
    UIComponent::UIComponent() {}

    UIComponent::UIComponent(const Size & pSize) : size(pSize)
    {
    }

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

    const Size & UIComponent::getSize() const
    {
        return size;
    }

    void UIComponent::setIsMouseOver(bool pIsMouseOver)
    {
        isMouseOver = pIsMouseOver;
    }

    void UIComponent::setIsMouseDown(bool pIsMouseDown)
    {
        isMouseDown = pIsMouseDown;
    }
}
