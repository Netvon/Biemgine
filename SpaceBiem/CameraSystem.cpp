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
    void CameraSystem::setGraphicsDevice(GraphicsDevice* graphicsDevice)
    {
        this->graphicsDevice = graphicsDevice;
    }

    void CameraSystem::before(const float deltaTime)
    {}

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

            float xDelta = camera->getWindowWidth() / 2 - pc->getOriginX();
            float yDelta = camera->getWindowHeight() / 2 - pc->getOriginY();

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
    {}

    void CameraSystem::onSceneSwitch()
    {
        if (graphicsDevice != nullptr)
            graphicsDevice->clear();
    }
}
