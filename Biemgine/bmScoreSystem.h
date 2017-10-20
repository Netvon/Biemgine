#pragma once
#include "bmSystem.h"
class bmScoreSystem :
	public bmSystem
{
public:
	bmScoreSystem();
	~bmScoreSystem();

    void update(const bmEntity& entity, const float deltaTime) override;
    void onSceneSwitch() override;
};

