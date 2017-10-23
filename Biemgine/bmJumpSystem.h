#pragma once
#include "bmSystem.h"
class bmJumpSystem :
    public bmSystem
{
public:

    void before() override;
    void update(const bmEntity& entity) override;

    void onSceneSwitch() override { };

private:
    bool shouldJump = false;
};

