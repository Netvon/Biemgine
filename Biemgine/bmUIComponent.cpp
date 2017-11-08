#include "components\bmUIComponent.h"

namespace biemgine {
    bmUIComponent::bmUIComponent() {}
    bmUIComponent::~bmUIComponent() {}

    void bmUIComponent::setComponentReference(bmComponent * component)
    {
        componentReference = component;
    }
}
