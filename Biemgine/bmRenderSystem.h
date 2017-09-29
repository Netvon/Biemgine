#pragma once
#include "bmSystem.h"
#include "bmEntity.h"

class bmRenderSystem : public bmSystem
{
public:

	void update(const bmEntity& entity) override;
};

