#include "UISystem.h"

namespace biemgine
{
    UISystem::~UISystem()
    {
    }

    void UISystem::before()
    {
        currentMouseLocation = getTransitionManager()->getInputManager()->getMouseLocation();
    }

    void UISystem::update(const Entity & entity)
    {
        if (!entity.hasComponent("ui"))
            return;


    }
}
