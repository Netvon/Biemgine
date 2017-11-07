#pragma once

#include "stdafx.h"
#include "..\components\bmOxygenComponent.h"

using namespace biemgine;
using std::map;

class bmOxygenUISystem : public bmSystem
{
public:

    bmOxygenUISystem() {};
    ~bmOxygenUISystem() {};

    void bmOxygenUISystem::setGraphicsDevice(GraphicsDevice* graphicsDevice);

    void before(const float deltaTime) override;
    void update(const bmEntity& entity, const float deltaTime) override;
    void after(const float deltaTime) override;

    void onSceneSwitch() override;

private:
    GraphicsDevice* graphicsDevice = nullptr;

    map<bmOxygenComponent*, bool> oxygenMap;

};

