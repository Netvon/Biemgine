#pragma once
#include "bmSystem.h"
class bmRotationSystem :
	public bmSystem
{
public:
	bmRotationSystem();
	~bmRotationSystem();

    void update(const bmEntity& entity) override;
};
