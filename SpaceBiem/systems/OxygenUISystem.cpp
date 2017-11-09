#include "stdafx.h"
#include "OxygenUISystem.h"

using biemgine::ColorComponent;
using biemgine::UIComponent;
using biemgine::PositionComponent;
using biemgine::RectangleComponent;

namespace spacebiem
{
    void OxygenUISystem::setGraphicsDevice(GraphicsDevice* graphicsDevice)
    {
        this->graphicsDevice = graphicsDevice;
    }

    void OxygenUISystem::before(const float deltaTime)
    {
    }

    void OxygenUISystem::update(const Entity & entity, const float deltaTime)
    {
        if (!entity.hasComponent("oxygen")) return;

        auto oc = entity.getComponent<OxygenComponent*>("oxygen");

        if (!entity.hasComponent("ui")) {
            if (oxygenMap.find(oc) == oxygenMap.end()) {
                oxygenMap[oc] = false;
            }
            return;
        }

        if (!entity.hasComponent("position")) return;
        if (!entity.hasComponent("color")) return;
        if (!entity.hasComponent("rectangle")) return;

        auto pc = entity.getComponent<PositionComponent*>("position");
        auto uc = entity.getComponent<UIComponent*>("ui");
        auto cc = entity.getComponent<ColorComponent*>("color");


        // If the UI doesn't have the component which to draw, pick one from the map.
        OxygenComponent* oRef = uc->getComponentReference<OxygenComponent*>();
        if (oRef == nullptr) {
            for (auto x : oxygenMap)
            {
                if (!x.second) {
                    uc->setComponentReference(x.first);
                    oRef = x.first;
                    break;
                }
            }
            if (oRef != nullptr) oxygenMap[oRef] = true;
            else return;
        }


        float oBar = (float)oRef->getOxygenAmount() / (float)oRef->getOxygenMax();


        auto rc = entity.getComponent<RectangleComponent*>("rectangle");
        rc->setWidth(transitionManager->getWindowWidth() * oBar);

    }

    void OxygenUISystem::after(const float deltaTime)
    {
    }

    void OxygenUISystem::onSceneSwitch()
    {
        if (graphicsDevice != nullptr)
            graphicsDevice->clear();
    }
}
