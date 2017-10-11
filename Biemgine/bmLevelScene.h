#pragma once
#include "bmScene.h"

class bmLevelScene :
	public bmScene
{
public:
    void input() override;
    void update() override;
    void render(const float deltaTime) override;
	void sceneCreated() override;

	bmLevelScene(bmSceneManager* manager/*, bmResourceManager* resourceManager*/) 
		: bmScene(manager/*, resourceManager*/) {};
};

