#pragma once
#include "bmSystem.h"
class bmScoreSystem :
	public bmSystem
{
public:
	bmScoreSystem();
	~bmScoreSystem();

    void update(const bmEntity& entity) override;
    void onSceneSwitch() override;
};

