#include "stdafx.h"
#include "bmRenderOxygenSystem.h"

void bmRenderOxygenSystem::setGraphicsDevice(GraphicsDevice* graphicsDevice)
{
    this->graphicsDevice = graphicsDevice;
}

void bmRenderOxygenSystem::before(const float deltaTime)
{
    graphicsDevice->clear();
}

void bmRenderOxygenSystem::update(const bmEntity & entity, const float deltaTime)
{
    if (!entity.hasComponent("oxygen")) return;

    auto oc = entity.getComponent<bmOxygenComponent*>("oxygen");

    if (!entity.hasComponent("ui")) {
        if (oxygenMap.find(oc) == oxygenMap.end()) {
            oxygenMap[oc] = false;
        }
        return;
    }

    if (!entity.hasComponent("position")) return;
    if (!entity.hasComponent("color")) return;

    auto pc = entity.getComponent<bmPositionComponent*>("position");
    auto uc = entity.getComponent<bmUIComponent*>("ui");
    auto cc = entity.getComponent<bmColorComponent*>("color");


    // If the UI doesn't have the component which to draw, pick one from the map.
    bmOxygenComponent* oRef = uc->getComponentReference<bmOxygenComponent*>();
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

    // Now draw!
    graphicsDevice->drawSquare(
        static_cast<int>(pc->getX()),
        static_cast<int>(pc->getY()),
        static_cast<int>(transitionManager->getWindowWidth() * oBar),
        static_cast<int>(10),
        cc->getColor(),
        pc->getRotation()
    );

}

void bmRenderOxygenSystem::after(const float deltaTime)
{
    graphicsDevice->present();
}

void bmRenderOxygenSystem::onSceneSwitch()
{
    if (graphicsDevice != nullptr)
        graphicsDevice->clear();
}
