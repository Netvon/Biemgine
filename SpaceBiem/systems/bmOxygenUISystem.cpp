#include "stdafx.h"
#include "bmOxygenUISystem.h"

void bmOxygenUISystem::setGraphicsDevice(GraphicsDevice* graphicsDevice)
{
    this->graphicsDevice = graphicsDevice;
}

void bmOxygenUISystem::before(const float deltaTime)
{
}

void bmOxygenUISystem::update(const bmEntity & entity, const float deltaTime)
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
    if (!entity.hasComponent("rectangle")) return;

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


    auto rc = entity.getComponent<bmRectangleComponent*>("rectangle");
    rc->setWidth(transitionManager->getWindowWidth() * oBar);

}

void bmOxygenUISystem::after(const float deltaTime)
{
}

void bmOxygenUISystem::onSceneSwitch()
{
    if (graphicsDevice != nullptr)
        graphicsDevice->clear();
}
