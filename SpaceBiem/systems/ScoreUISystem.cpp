#include "stdafx.h"
#include <windows.h>
#include <Lmcons.h>
#include "ScoreUISystem.h"

using biemgine::TextComponent;
using biemgine::PositionComponent;
using biemgine::UIComponent;
using biemgine::Color;

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

        TCHAR user[UNLEN + 1];
        DWORD size = UNLEN + 1;
        string name = "Mr. NoName";

        if (GetUserName((TCHAR*)user, &size)) {
            wstring test(&user[0]);
            string stringName(test.begin(), test.end());
            name = stringName;
        }

        auto tx = entity.getComponent<TextComponent*>("text");

        if (name == oRef->getName()) {
            tx->setText(oRef->getName() + ": " + std::to_string((int)oRef->getScore()), { 66, 113, 244 });
        }
        else {
            tx->setText(oRef->getName() + ": " + std::to_string((int)oRef->getScore()), { 255, 255, 255 });
        }
    }

    void ScoreUISystem::after(const float deltaTime) {}

    void ScoreUISystem::onSceneSwitch()
    {
        if (graphicsDevice != nullptr)
            graphicsDevice->clear();
    }
}
