#pragma once
#include "..\stdafx.h"
#include "..\core\Window.h"
#include "bmInputManager.h"

class bmSceneManager;
class bmStateManager
{
public:
    bmStateManager(
        const bmSceneManager* pSceneManager,
        const Window* pWindow
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

    void setInputManager(const bmInputManager* manager) {
        inputManager = manager;
    }

    const bmInputManager* getInputManager() const
    {
        return inputManager;
    }

private:
    const bmSceneManager* sceneManager = nullptr;
    const bmInputManager* inputManager = nullptr;
    const Window* window = nullptr;

    bool paused = false;
};

