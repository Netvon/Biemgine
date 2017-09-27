#include "stdafx.h"
#include "bmSceneManager.h"


bmSceneManager* bmSceneManager::smInstance = 0;

bmSceneManager* bmSceneManager::instance()
{
	if (smInstance == 0) smInstance = new bmSceneManager();

	return smInstance;
}

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
		currentScene = NULL;
	}

	switch (nextScene) {
	case bmScene_level:

		nextScene = bmScene_NULL;

		currentScene = new bmLevelScene();
		currentScene->start(currentWindow);

		break;
	case bmScene_menu:

		nextScene = bmScene_NULL;

		currentScene = new bmMenuScene();
		currentScene->start(currentWindow);

		break;
	default:
		return false;
		break;
	}

	return true;
}

