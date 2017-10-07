#pragma once
#include "bmScene.h"

class bmMenuScene :
	public bmScene
{
public:
	void update(float deltaTime) override;
	void sceneCreated() override;

	bmMenuScene(bmSceneManager* manager, bmResourceManager* resourceManager)
		: bmScene(manager, resourceManager) {};
};

