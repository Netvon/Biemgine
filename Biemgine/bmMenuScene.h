#pragma once
#include "bmScene.h"
#include "bmRectangle.h"

class bmMenuScene :
	public bmScene
{
public:
	void update(float deltaTime) override;
	void created() override;

	bmMenuScene(bmSceneManager* manager) : bmScene(manager) {};
};

