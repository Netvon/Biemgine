#include "stdafx.h"
#include "bmMenuScene.h"
#include "bmSceneManager.h"


void bmMenuScene::created()
{
	/*bmRectangle* c1 = new bmRectangle(0, 0, 100, 100);
	addComponent(c1);*/

	cout << "MenuScene created" << endl;
}

void bmMenuScene::update(float deltaTime)
{
	if (im.isKeyDown("Q")) {
		signalQuit();
	}

	if (im.isKeyDown("S")) {
		sceneManager->changeScene(bmScene_level);
	}
}