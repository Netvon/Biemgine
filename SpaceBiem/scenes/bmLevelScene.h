#pragma once
using namespace biemgine;

class bmLevelScene :
    public bmScene
{
public:
    void input() override;
    void update() override;
    void render(const float deltaTime) override;
    void sceneCreated() override;
    void sceneEnd() override;

    bmLevelScene(bmStateManager& manager)
        : bmScene(manager) {};

private:
    bool isPauseButtonDown = false;
};

