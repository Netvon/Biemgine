#include "components\UIComponent.h"

namespace biemgine
{
    UIComponent::UIComponent() {}
    UIComponent::~UIComponent() {}

    void UIComponent::setComponentReference(Component * component)
    {
        componentReference = component;
    }
}
