#pragma once
#include "bmScene.h"
#include "bmRectangle.h"

class bmLevelScene :
	public bmScene
{
public:
	void update(float deltaTime) override;
	void sceneCreated() override;

	bmLevelScene(bmSceneManager* manager, bmResourceManager* resourceManager) 
		: bmScene(manager, resourceManager) {};
};

