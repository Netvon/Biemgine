#include "stdafx.h"
#include "ResourceUISystem.h"
#include "..\components\ResourceBonusComponent.h"

using biemgine::TextComponent;
using biemgine::PositionComponent;
using biemgine::UIComponent;
using biemgine::ColorComponent;
using biemgine::Color;

namespace spacebiem
{
    void ResourceUISystem::update(const Entity & entity)
    {
        if (entity.hasComponent("resources")) {
            auto oc = entity.getComponent<ResourceComponent>("resources");

            if (resourceMap.find(oc) == resourceMap.end()) {
                resourceMap[oc] = false;
            }

            return;
        }

        if (!entity.hasComponent("resourcebonus")
            || !entity.hasComponent("color")
            || !entity.hasComponent("position")
            || !entity.hasComponent("text"))
            return;

        auto pc = entity.getComponent<PositionComponent>("position");
        auto rbc = entity.getComponent<ResourceBonusComponent>("resourcebonus");
        auto cc = entity.getComponent<ColorComponent>("color");
        auto tx = entity.getComponent<TextComponent>("text");
        auto uc = entity.getComponent<UIComponent>("ui");

        auto oRef = uc->getComponentReference<ResourceComponent>();

        if (oRef == nullptr) {
            for (auto& x : resourceMap)
            {
                if (!x.second) {
                    uc->setComponentReference(x.first);
                    oRef = x.first;
                    break;
                }
            }
        }

        if (oRef == nullptr) {
            tx->setText(std::to_string(rbc->getAmount()), cc->getColor());  
        }
        else {
            for (auto& x : oRef->getResources())
            {
                if (x.first == rbc->getName()) {
                    tx->setText(std::to_string(x.second), cc->getColor());
                }
            }
        }
    }
}
