#pragma once

#include "Biemgine.h"

using namespace biemgine;

class bmJumpSystem :
    public bmSystem
{
public:
    void update(const bmEntity& entity) override;
    void onSceneSwitch() override { };
};

