#include "stdafx.h"
#include "CameraSystem.h"

#include "../components/PositionComponent.h"


namespace biemgine
{
    void CameraSystem::update(const Entity & entity)
    {
        if (entity.hasComponent("camera") && entity.hasComponent("position"))
        {
            auto pc = entity.getComponent<PositionComponent>("position");
            auto camera = entity.getComponent<CameraComponent>("camera");

            camera->setWindowWidth(getStateManager()->getWindowWidth());
            camera->setWindowHeight(getStateManager()->getWindowHeight());

            camera->setOriginX(pc->getOriginX());
            camera->setOriginY(pc->getOriginY());

            int xDelta = static_cast<int>((camera->getWindowWidth()) / 2 - static_cast<int>(pc->getOriginX()));
            int yDelta = static_cast<int>((camera->getWindowHeight()) / 2 - static_cast<int>(pc->getOriginY()));

            camera->setDeltaX(static_cast<float>(xDelta));
            camera->setDeltaY(static_cast<float>(yDelta));
        } 
    }
}
