#pragma once

#include "bmSystem.h"

class bmMovementSystem :
	public bmSystem
{
public:
    void update(const bmEntity& entity) override;
    void onSceneSwitch() override { };
};
