#include "stdafx.h"
#include "OxygenUISystem.h"

using biemgine::Color;
using biemgine::ColorComponent;
using biemgine::UIComponent;
using biemgine::PositionComponent;
using biemgine::RectangleComponent;
using biemgine::TextureComponent;

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
        if (!entity.hasComponent("texture")) return;

        auto pc = entity.getComponent<PositionComponent*>("position");
        auto uc = entity.getComponent<UIComponent*>("ui");

        auto tc = entity.getComponents<TextureComponent*>("texture");
        TextureComponent* texture = entity.getComponent<TextureComponent*>("texture");

        for (auto tex : tc) {
            if (tex->getTag() == "oxygenbar") texture = tex;
        }

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


        float oBar = oRef->getOxygenAmount() / static_cast<float>(oRef->getOxygenMax());

        Color dangerRedColor = {204, 94, 94};
        Color newColor;
        newColor.r = dangerRedColor.r + ((texture->getOriginalColor().r - dangerRedColor.r) * oBar);
        newColor.g = dangerRedColor.g + ((texture->getOriginalColor().g - dangerRedColor.g) * oBar);
        newColor.b = dangerRedColor.b + ((texture->getOriginalColor().b - dangerRedColor.b) * oBar);

        texture->setWidth(texture->getOriginalWidth() * oBar);
        texture->setColor(newColor);
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
