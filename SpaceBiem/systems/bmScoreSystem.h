#pragma once

#include "Biemgine.h"
using namespace biemgine;

class bmScoreSystem :
    public bmSystem
{
public:
    bmScoreSystem();
    ~bmScoreSystem();

    void update(const bmEntity& entity) override;
    void onSceneSwitch() override;
};

