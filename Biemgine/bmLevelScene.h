#pragma once
#include "bmScene.h"
#include "bmRectangle.h"

class bmLevelScene :
	public bmScene
{
public:
	void update(float deltaTime) override;
	void created() override;

	bmLevelScene(bmSceneManager* manager, bmResourceManager* resourceManager) 
		: bmScene(manager, resourceManager) {};
};

