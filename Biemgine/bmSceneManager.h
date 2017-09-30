#pragma once
#include "bmScene.h"
#include "bmSceneType.h"
#include "bmLevelScene.h"
#include "bmMenuScene.h"
#include "bmResourceManager.h"

class bmSceneManager
{
public:

	void setWindow(SdlWindow*);
	void changeScene(bmSceneType);
	bool checkNextScene();

	bmSceneManager() {};

private:
	bmScene* currentScene = nullptr;
	SdlWindow* currentWindow;
	bmResourceManager resourceManager;

	int nextScene;
};

