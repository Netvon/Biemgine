#include "stdafx.h"
#include "CameraSystem.h"

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
            auto cc = entity.getComponent<Camera*>("camera");

            float xDelta = 960 - pc->getOriginX();
            float yDelta = 540 - pc->getOriginY();

            cc->setDeltaX(xDelta);
            cc->setDeltaY(yDelta);

            camera = cc;
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
