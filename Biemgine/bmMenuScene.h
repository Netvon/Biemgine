#pragma once
#include "bmScene.h"
#include "bmRectangle.h"

class bmMenuScene :
	public bmScene
{
public:
	bmMenuScene();

	void update() override;
	void created() override;

private:

};

