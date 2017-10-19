#pragma once

#include "bmSystem.h"
#include "bmOxygenComponent.h"
#include "bmPositionComponent.h"
#include "bmUIComponent.h"
#include "bmColorComponent.h"
#include "GraphicsDevice.h"

class bmRenderOxygenSystem : public bmSystem
{
public:

    bmRenderOxygenSystem() {};
    ~bmRenderOxygenSystem() {};

    void bmRenderOxygenSystem::setGraphicsDevice(GraphicsDevice* graphicsDevice);

    void before(const float deltaTime) override;
    void update(const bmEntity& entity, const float deltaTime) override;
    void after(const float deltaTime) override;

    void onSceneSwitch() override;

private:
    GraphicsDevice* graphicsDevice = nullptr;

    std::map<bmOxygenComponent*, bool> oxygenMap;

};

