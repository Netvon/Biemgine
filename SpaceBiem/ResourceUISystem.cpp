#include "stdafx.h"
#include "ResourceUISystem.h"
#include "components\ResourceBonusComponent.h"

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
        if (!entity.hasComponent("resources")) return;

        auto oc = entity.getComponent<ResourceComponent*>("resources");

        if (!entity.hasComponent("ui")) {
            if (resourceMap.find(oc) == resourceMap.end()) {
                resourceMap[oc] = false;
            }
            return;
        }

        if (!entity.hasComponent("position")) return;
        if (!entity.hasComponent("resourcebonus")) return;
        if (!entity.hasComponent("text")) return;

        auto pc = entity.getComponent<PositionComponent*>("position");
        auto rbc = entity.getComponent<ResourceBonusComponent*>("resourcebonus");
        auto uc = entity.getComponent<UIComponent*>("ui");

        ResourceComponent* oRef = uc->getComponentReference<ResourceComponent*>();

        if (oRef == nullptr) {
            for (auto x : resourceMap)
            {
                if (!x.second) {
                    uc->setComponentReference(x.first);
                    oRef = x.first;
                    break;
                }
            }

            if (oRef != nullptr) resourceMap[oRef] = true;
            else oRef = oc;
        }


    }

    void ResourceUISystem::after(const float deltaTime) {}

    void ResourceUISystem::onSceneSwitch()
    {
        if (graphicsDevice != nullptr)
            graphicsDevice->clear();
    }
}
