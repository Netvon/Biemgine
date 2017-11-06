#pragma once
#include "Window.h"
#include "bmInputManager.h"

class bmSceneManager;
class bmStateManager
{
public:
    bmStateManager(
        bmSceneManager* pSceneManager,
        Window* pWindow
    ): sceneManager(pSceneManager), window(pWindow) {};

    ~bmStateManager();

    void gameOverTransition();

    void quitLevelTransition();
    void startLevelTransition();

    int getWindowWidth() const;
    int getWindowHeight() const;

    void pauseGame();
    void resumeGame();
    bool isPaused();

    void drawOverlay();
    void drawBackground();

    void setInputManager(bmInputManager* manager) {
        inputManager = manager;
    }

    bmInputManager* getInputManager() const
    {
        return inputManager;
    }

private:
    bmSceneManager* sceneManager = nullptr;
    bmInputManager* inputManager = nullptr;
    Window* window = nullptr;

    bool paused = false;
};

