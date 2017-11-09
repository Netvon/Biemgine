#include "stdafx.h"
#include "ResourceUISystem.h"

using biemgine::TextComponent;
using biemgine::PositionComponent;
using biemgine::UIComponent;

namespace spacebiem
{
    void ResourceUISystem::setGraphicsDevice(GraphicsDevice* graphicsDevice)
    {
        this->graphicsDevice = graphicsDevice;
    }

    void ResourceUISystem::before(const float deltaTime) {}

    void ResourceUISystem::update(const Entity & entity, const float deltaTime)
    {
        
    }

    void ResourceUISystem::after(const float deltaTime) {}

    void ResourceUISystem::onSceneSwitch()
    {
        if (graphicsDevice != nullptr)
            graphicsDevice->clear();
    }
}
