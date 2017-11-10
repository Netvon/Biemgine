#include "stdafx.h"
#include "StateManager.h"
#include "SceneManager.h"

namespace biemgine
{
    StateManager::~StateManager() {}

    void StateManager::gameOverTransition()
    {
        //sceneManager->changeScene(Scene_menu);
    }

    void StateManager::quitLevelTransition()
    {
        //sceneManager->changeScene(Scene_menu);
    }

    void StateManager::startLevelTransition()
    {
        //sceneManager->changeScene(Scene_level);
    }

    int StateManager::getWindowWidth() const
    {
        return window->getWidth();
    }

    int StateManager::getWindowHeight() const
    {
        return window->getHeight();
    }

    void StateManager::pauseGame()
    {
        paused = true;
    }

    void StateManager::resumeGame()
    {
        paused = false;
    }

    bool StateManager::isPaused()
    {
        return paused;
    }

    void StateManager::drawOverlay()
    {
        if (paused) {
            auto gd = window->getGraphicsDevice();

            int x = 20;
            int y = 60;

            gd->drawText("The game is paused.", x, y, { 255, 255, 255, 255 }, 20);
            gd->drawText("Press 'P' to resume the game...", x, y + 25, { 255, 255, 255, 255 }, 20);
        }
    }

    void StateManager::drawBackground()
    {
        auto gd = window->getGraphicsDevice();

        gd->drawTexture("textures/space.jpg", 0, 0, getWindowWidth(), getWindowHeight(), 0.f, { 255, 255, 255, 255 });
    }
}
