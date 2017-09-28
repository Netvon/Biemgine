#include "stdafx.h"
#include "bmSceneManager.h"

void bmSceneManager::setWindow(SdlWindow* window)
{
	currentWindow = window;
}


void bmSceneManager::changeScene(bmSceneType changingScene)
{
	
	nextScene = changingScene;

	if (currentScene != nullptr) currentScene->signalQuit();

}

bool bmSceneManager::checkNextScene() 
{

	if (currentScene != nullptr) {
		delete currentScene;
	}

	switch (nextScene) {
	case bmScene_level:

		nextScene = bmScene_NULL;

		currentScene = new bmLevelScene(this);
		currentScene->start(currentWindow);

		break;
	case bmScene_menu:

		nextScene = bmScene_NULL;

		currentScene = new bmMenuScene(this);
		currentScene->start(currentWindow);

		break;
	default:
		return false;
		break;
	}

	return true;
}

