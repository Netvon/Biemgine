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
    void OxygenUISystem::update(const Entity & entity)
    {
        if (!entity.hasComponent("oxygen")) return;

        auto oc = entity.getComponent<OxygenComponent>("oxygen");

        if (!entity.hasComponent("ui")) {
            if (oxygenMap.find(oc) == oxygenMap.end()) {
                oxygenMap[oc] = false;
            }
            return;
        }

        if (!entity.hasComponent("position") || !entity.hasComponent("texture"))
            return;

        auto pc = entity.getComponent<PositionComponent>("position");
        auto uc = entity.getComponent<UIComponent>("ui");

        auto tc = entity.getComponents<TextureComponent>("texture");
        std::shared_ptr<TextureComponent> texture = nullptr;

        for (auto tex : tc) {
            if (tex->getTag() == "oxygenbar") texture = tex;
        }

        // If the UI doesn't have the component which to draw, pick one from the map.
        auto oRef = uc->getComponentReference<OxygenComponent>();
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

        Color dangerRedColor { 204, 94, 94 };
        Color newColor{
            dangerRedColor.r + static_cast<char>((texture->getOriginalColor().r - dangerRedColor.r) * oBar),
            dangerRedColor.g + static_cast<char>((texture->getOriginalColor().g - dangerRedColor.g) * oBar),
            dangerRedColor.b + static_cast<char>((texture->getOriginalColor().b - dangerRedColor.b) * oBar)
        };

        texture->setWidth(static_cast<int>(texture->getOriginalWidth() * oBar));
        texture->setColor(newColor);
    }

    System::required_components OxygenUISystem::requirements() const
    {
        return {
            //System::requirement<PositionComponent>(),
            System::requirement<OxygenComponent>(),
            System::requirement<UIComponent, System::optional>(),
            System::requirement<TextureComponent, System::optional>(),
            System::requirement<PositionComponent, System::optional>()
        };
    }
}
