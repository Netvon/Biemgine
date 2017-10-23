#pragma once
#include "bmScene.h"

class bmMenuScene :
    public bmScene
{
public:
    void input() override;
    void update() override;
    void render(const float deltaTime) override;
    void sceneCreated() override;

    bmMenuScene(bmStateManager* manager/*, bmResourceManager* resourceManager*/)
        : bmScene(manager/*, resourceManager*/) {};
};

