#pragma once

#include "bmSystem.h"
#include "bmScoreComponent.h"
#include "bmTextComponent.h"
#include "bmPositionComponent.h"
#include "bmUIComponent.h"
#include "bmColorComponent.h"
#include "GraphicsDevice.h"

class bmScoreUISystem : public bmSystem
{
public:

    bmScoreUISystem() {};
    ~bmScoreUISystem() {};

    void bmScoreUISystem::setGraphicsDevice(GraphicsDevice* graphicsDevice);

    void before(const float deltaTime) override;
    void update(const bmEntity& entity, const float deltaTime) override;
    void after(const float deltaTime) override;

    void onSceneSwitch() override;

private:
    GraphicsDevice* graphicsDevice = nullptr;

    std::map<bmScoreComponent*, bool> scoreMap;

};

