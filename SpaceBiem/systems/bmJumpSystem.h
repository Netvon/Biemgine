#pragma once
#include "bmSystem.h"
class bmJumpSystem :
    public bmSystem
{
public:
    void update(const bmEntity& entity) override;
    void onSceneSwitch() override { };
};

