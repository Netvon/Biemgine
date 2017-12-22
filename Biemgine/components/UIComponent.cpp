#include "UIComponent.h"

using std::function;

namespace biemgine
{
    UIComponent::UIComponent(bool pEnabled): enabled(pEnabled) {}

    UIComponent::UIComponent(const SizeRect & pSize, function<void(StateManager*)> onClick, function<void(StateManager*)> onEnter, bool pEnabled) : size(pSize), onClick(onClick), onEnter(onEnter), enabled(pEnabled)
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

    const SizeRect & UIComponent::getSize() const
    {
        return size;
    }

    function<void(StateManager*)> UIComponent::getIsClicked() const
    {
        return onClick;
    }

    function<void(StateManager*)> UIComponent::getIsEntered() const
    {
        return onEnter;
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
