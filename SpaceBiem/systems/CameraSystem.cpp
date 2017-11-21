#include "stdafx.h"
#include "CameraSystem.h"

using biemgine::Rect;
using biemgine::Color;
using biemgine::ColorComponent;
using biemgine::UIComponent;
using biemgine::PositionComponent;
using biemgine::RectangleComponent;
using biemgine::TextureComponent;

namespace spacebiem
{
    void CameraSystem::update(const Entity & entity)
    {
        if (!entity.hasComponent("position") || entity.hasComponent("ui"))
            return;

        auto pc = entity.getComponent<PositionComponent*>("position");

        if (entity.hasComponent("camera"))
        {
            camera = entity.getComponent<CameraComponent*>("camera");

            camera->setWindowWidth(getStateManager()->getWindowWidth());
            camera->setWindowHeight(getStateManager()->getWindowHeight());

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
}
