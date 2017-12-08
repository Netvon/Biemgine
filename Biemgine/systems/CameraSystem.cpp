#include "stdafx.h"
#include "CameraSystem.h"

#include "../components/PositionComponent.h"


namespace biemgine
{
    void CameraSystem::update(const Entity & entity)
    {
        if (!entity.hasComponent("position") || entity.hasComponent("ui"))
            return;

        auto pc = entity.getComponent<PositionComponent>("position");

        if (entity.hasComponent("camera"))
        {
            camera = entity.getComponent<CameraComponent>("camera");

            camera->setWindowWidth(getStateManager()->getWindowWidth());
            camera->setWindowHeight(getStateManager()->getWindowHeight());

            camera->setOriginX(pc->getOriginX());
            camera->setOriginY(pc->getOriginY());

            int xDelta = static_cast<int>((camera->getWindowWidth()) / 2 - static_cast<int>(pc->getOriginX()));
            int yDelta = static_cast<int>((camera->getWindowHeight()) / 2 - static_cast<int>(pc->getOriginY()));

            camera->setDeltaX(static_cast<float>(xDelta));
            camera->setDeltaY(static_cast<float>(yDelta));
        }

        if (camera != nullptr)
        {
            pc->setOffsetX(camera->getDeltaX());
            pc->setOffsetY(camera->getDeltaY());
        }
    }

    System::required_components CameraSystem::requirements() const
    {
        return {
            System::requirement<PositionComponent>(),
            System::requirement<CameraComponent, System::optional>()
        };
    }
}
