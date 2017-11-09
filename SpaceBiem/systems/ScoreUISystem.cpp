#include "stdafx.h"
#include "ScoreUISystem.h"

using biemgine::TextComponent;
using biemgine::PositionComponent;
using biemgine::UIComponent;

namespace spacebiem
{
    void ScoreUISystem::setGraphicsDevice(GraphicsDevice* graphicsDevice)
    {
        this->graphicsDevice = graphicsDevice;
    }

    void ScoreUISystem::before(const float deltaTime) {}

    void ScoreUISystem::update(const Entity & entity, const float deltaTime)
    {
        if (!entity.hasComponent("score")) return;

        auto oc = entity.getComponent<ScoreComponent*>("score");

        if (!entity.hasComponent("ui")) {
            if (scoreMap.find(oc) == scoreMap.end()) {
                scoreMap[oc] = false;
            }
            return;
        }

        if (!entity.hasComponent("position")) return;

        auto pc = entity.getComponent<PositionComponent*>("position");
        auto uc = entity.getComponent<UIComponent*>("ui");

        if (uc->getIsMouseDown()) {
            printf("%i keydown\n", entity.getId());
        }

        if (uc->getIsMouseOver()) {
            printf("%i mouseover\n", entity.getId());
        }

        // If the UI doesn't have the component which to draw, pick one from the map.
        ScoreComponent* oRef = uc->getComponentReference<ScoreComponent*>();

        if (oRef == nullptr) {
            for (auto x : scoreMap)
            {
                if (!x.second) {
                    uc->setComponentReference(x.first);
                    oRef = x.first;
                    break;
                }
            }

            if (oRef != nullptr) scoreMap[oRef] = true;
            else oRef = oc;
        }

        auto tx = entity.getComponent<TextComponent*>("text");
        tx->setText(oRef->getName() + ": " + std::to_string((int)oRef->getScore()));
    }

    void ScoreUISystem::after(const float deltaTime)
    {
        /*if (getTransitionManager()->getInputManager()->isLeftMouseDown()) {
            auto l = getTransitionManager()->getInputManager()->getMouseLocation();
            printf("{%i,%i}\n", l.x, l.y);
        }*/
    }

    void ScoreUISystem::onSceneSwitch()
    {
        if (graphicsDevice != nullptr)
            graphicsDevice->clear();
    }
}
