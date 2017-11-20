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
    void CameraSystem::before(const float deltaTime)
    {

    }

    void CameraSystem::update(const Entity & entity, const float deltaTime)
    {
        if (!entity.hasComponent("position") || entity.hasComponent("ui"))
            return;

        auto pc = entity.getComponent<PositionComponent*>("position");

        if (entity.hasComponent("camera"))
        {
            camera = entity.getComponent<Camera*>("camera");

            camera->setWindowWidth(getStateManager()->getWindowWidth());
            camera->setWindowHeight(getStateManager()->getWindowHeight());

            float xDelta = static_cast<float>(camera->getWindowWidth()) / 2.0f - pc->getOriginX();
            float yDelta = static_cast<float>(camera->getWindowHeight()) / 2.0f - pc->getOriginY();

            camera->setDeltaX(xDelta);
            camera->setDeltaY(yDelta);

            //Rect rect = entity.getBounds();
            int test = 0;
        }

        if (camera != nullptr)
        {
            pc->setOffsetX(camera->getDeltaX());
            pc->setOffsetY(camera->getDeltaY());
        }
      
    }

    void CameraSystem::after(const float deltaTime)
    {

    }

    void CameraSystem::onSceneSwitch()
    {

    }
}
