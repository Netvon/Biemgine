#include "stdafx.h"
#include "bmLevelScene.h"
#include "bmSceneManager.h"
#include "bmPlayerEntity.h"


void bmLevelScene::sceneCreated()
{
	//bmRectangle* c1 = new bmRectangle(0, 0, 100, 100);
	//addComponent(c1);

	cout << "LevelScene created" << endl;


	// Setup the scene with entities

	getEntityManager().addEntity(new bmPlayerEntity(0, 0, 255, 0, 0, 15, 25));
	getEntityManager().addEntity(new bmPlayerEntity(100, 100, 0, 255, 0, 15, 25));
	getEntityManager().addEntity(new bmPlayerEntity(200, 200, 0, 0, 255, 15, 25));

	// Create and add Player
	// Create and add Planets


}

void bmLevelScene::update(float deltaTime)
{
	if (im.isKeyDown("Q")) {
		signalQuit();
	}

	if (im.isKeyDown("A")) {
		getSceneManager().changeScene(bmScene_menu);
	}


	// Give the input data to the entitymanager, so he can fill the inputcomponents


	// Update everything...
	updateEntities();
}