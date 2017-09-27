#pragma once
#include "bmScene.h"
#include "bmRectangle.h"

class bmMenuScene :
	public bmScene
{
public:
	bmMenuScene();

	void update(float deltaTime) override;
	void created() override;

private:

};

