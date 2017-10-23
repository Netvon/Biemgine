#pragma once
#include "bmStateManager.h"
#include "bmSceneType.h"
#include "bmLevelScene.h"
#include "bmMenuScene.h"
#include "bmResourceManager.h"

class bmSceneManager
{
public:

    void createStateManager(Window* window);
    void changeScene(bmSceneType);
    bool checkNextScene();

    bmSceneManager() {};
    ~bmSceneManager();

    bmStateManager* getTransitionManager() {
        return transitionManager;
    }

private:
    bmScene* currentScene = nullptr;
    Window* currentWindow;
    bmStateManager* transitionManager;

    int nextScene;
};

