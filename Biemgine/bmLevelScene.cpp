#include "stdafx.h"
#include "bmLevelScene.h"
#include "bmSceneManager.h"
#include "bmPlayerEntity.h"


void bmLevelScene::created()
{
	bmRectangle* c1 = new bmRectangle(0, 0, 100, 100);
	addComponent(c1);

	cout << "LevelScene created" << endl;


	// Setup the scene with entities

	entityManager->AddEntity(new bmPlayerEntity());
	entityManager->AddEntity(new bmPlayerEntity());
	entityManager->AddEntity(new bmPlayerEntity());

	// Create and add Player
	// Create and add Planets


}

void bmLevelScene::update()
{
	if (im.isKeyDown("Q")) {
		signalQuit();
	}

	if (im.isKeyDown("A")) {
		bmSceneManager::instance()->changeScene(bmScene_menu);
	}


	// Give the input data to the entitymanager, so he can fill the inputcomponents


	// Update everything...
	systemManager->updateAll(entityManager->entities);
	
	
}