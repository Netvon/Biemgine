#pragma once
#include "bmScene.h"
class bmPlanetScene :
	public bmScene
{
public:
	void update() override;
	void created() override;

private:
	//void sierpinski(int levels, float x, float y, float width, float height);
};

