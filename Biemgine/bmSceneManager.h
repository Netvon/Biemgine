#pragma once
#include "bmTransitionManager.h"
#include "bmSceneType.h"
#include "bmLevelScene.h"
#include "bmMenuScene.h"
#include "bmResourceManager.h"

class bmSceneManager
{
public:

    void setWindow(Window*);
    void changeScene(bmSceneType);
    bool checkNextScene();

    bmSceneManager() {};
    ~bmSceneManager();

private:
    bmScene* currentScene = nullptr;
    Window* currentWindow;
    bmTransitionManager* transitionManager;

    int nextScene;
};

