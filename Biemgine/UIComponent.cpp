#include "components\UIComponent.h"

using std::function;

namespace biemgine
{
    UIComponent::UIComponent() {}

    UIComponent::UIComponent(const Size & pSize, function<void(StateManager*)> onClick) : size(pSize), onClick(onClick)
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

    function<void(StateManager*)> UIComponent::getIsClicked() const
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
