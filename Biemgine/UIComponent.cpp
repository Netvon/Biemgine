#include "components\UIComponent.h"

namespace biemgine
{
    UIComponent::UIComponent() {}

    UIComponent::UIComponent(const Size & pSize, std::function<void(StateManager*)> onClick) : size(pSize)
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

    std::function<void(const StateManager*)> UIComponent::getIsClicked() const
    {
        return onClick;
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
