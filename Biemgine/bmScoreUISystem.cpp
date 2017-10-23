#include "stdafx.h"
#include "bmScoreUISystem.h"

void bmScoreUISystem::setGraphicsDevice(GraphicsDevice* graphicsDevice)
{
    this->graphicsDevice = graphicsDevice;
}

void bmScoreUISystem::before(const float deltaTime)
{
}

void bmScoreUISystem::update(const bmEntity & entity, const float deltaTime)
{
    if (!entity.hasComponent("score")) return;

    auto oc = entity.getComponent<bmScoreComponent*>("score");

    if (!entity.hasComponent("ui")) {
        if (scoreMap.find(oc) == scoreMap.end()) {
            scoreMap[oc] = false;
        }
        return;
    }

    if (!entity.hasComponent("position")) return;

    auto pc = entity.getComponent<bmPositionComponent*>("position");
    auto uc = entity.getComponent<bmUIComponent*>("ui");

    // If the UI doesn't have the component which to draw, pick one from the map.
    bmScoreComponent* oRef = uc->getComponentReference<bmScoreComponent*>();
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

    auto tx = entity.getComponent<bmTextComponent*>("text");
    tx->setText("Score: " + std::to_string(oRef->getScore()));
}

void bmScoreUISystem::after(const float deltaTime)
{
}

void bmScoreUISystem::onSceneSwitch()
{
    if (graphicsDevice != nullptr)
        graphicsDevice->clear();
}
