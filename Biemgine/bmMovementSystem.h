#pragma once

#include "bmSystem.h"

class bmMovementSystem :
	public bmSystem
{
public:
    void before() override;
    void update(const bmEntity& entity) override;

    void onSceneSwitch() override { };

private:
    bool shouldLeft = false;
    bool shouldRight = false;
};


