#pragma once
#include "Window.h"

class bmSceneManager;
class bmTransitionManager
{
public:
    bmTransitionManager(bmSceneManager* pSceneManager, Window* pWindow): sceneManager(pSceneManager), window(pWindow) {};

    void gameOverTransition();

    void quitLevelTransition();
    void startLevelTransition();

    int getWindowWidth() const;
    int getWindowHeight() const;

private:
    bmSceneManager* sceneManager = nullptr;
    Window* window = nullptr;


};

