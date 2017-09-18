#include "stdafx.h"
#include "bmPlanetScene.h"
#include "bmRectangle.h"

void bmPlanetScene::created()
{
	bmRectangle* c1 = new bmRectangle(0, 0, 100, 100);
	addComponent(c1);
}

void bmPlanetScene::update()
{
	if (im.isKeyDown("Q")) {
		signalQuit();
	}
}
