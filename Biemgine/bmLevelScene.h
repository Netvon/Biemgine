#pragma once
#include "bmScene.h"
#include "bmStateManager.h"

class bmLevelScene :
    public bmScene
{
public:
    void input() override;
    void update() override;
    void render(const float deltaTime) override;
    void sceneCreated() override;
    void sceneEnd() override;

    bmLevelScene(bmStateManager* manager/*, bmResourceManager* resourceManager*/)
        : bmScene(manager/*, resourceManager*/) {};

private:
    bool isPauseButtonDown = false;
};

