#pragma once
#include "bmScene.h"
#include "bmSceneType.h"
#include "bmLevelScene.h"
#include "bmMenuScene.h"

class bmSceneManager
{
public:
	static bmSceneManager* instance();

	void setWindow(SdlWindow*);
	void changeScene(bmSceneType);
	bool checkNextScene();

private:
	bmScene* currentScene = nullptr;
	SdlWindow* currentWindow;
	static bmSceneManager* smInstance;
	int nextScene;


	bmSceneManager() {};
};

