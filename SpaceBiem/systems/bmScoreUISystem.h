#pragma once

#include "stdafx.h"
#include "..\components\bmScoreComponent.h"

using namespace biemgine;

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

