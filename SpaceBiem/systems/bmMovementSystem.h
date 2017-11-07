#pragma once

using namespace biemgine;

class bmMovementSystem :
    public bmSystem
{
public:
    void update(const bmEntity& entity) override;
    void onSceneSwitch() override { };
};
