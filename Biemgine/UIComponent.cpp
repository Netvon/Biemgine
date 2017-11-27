#include "components\UIComponent.h"

using std::function;

namespace biemgine
{
    UIComponent::UIComponent(bool pEnabled): enabled(pEnabled) {}

    UIComponent::UIComponent(const Size & pSize, function<void(StateManager*)> onClick, bool pEnabled) : size(pSize), onClick(onClick), enabled(pEnabled)
    {
    }

    UIComponent::~UIComponent() {}

    void UIComponent::setComponentReference(std::shared_ptr<Component> component)
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

    bool UIComponent::isEnabled() const
    {
        return enabled;
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
