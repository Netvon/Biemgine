#include "stdafx.h"
#include "StateManager.h"
#include "SceneManager.h"

namespace biemgine
{
    StateManager::~StateManager() {}


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

    void StateManager::drawOverlay(Font font)
    {
        if (paused) {
            auto gd = window->getGraphicsDevice();

            int x = getWindowWidth()/2;
            int y = 60;

            gd->drawText(font, "The game is paused.", x, y, { 255, 255, 255, 255 }, 20, biemgine::NONE, true);
            gd->drawText(font, "Press 'P' to resume the game...", x, y + 25, { 255, 255, 255, 255 }, 20, biemgine::NONE, true);
        }
    }

    void StateManager::drawBackground(const string& backgroundPath)
    {
        auto gd = window->getGraphicsDevice();

        gd->drawTexture(backgroundPath, 0, 0, getWindowWidth(), getWindowHeight(), 0.f, { 255, 255, 255, 255 });
    }

    SceneManager & StateManager::getSceneManager() const
    {
        return *sceneManager;
    }

    Entity * StateManager::getEntity(int id) const
    {
        return getSceneManager()
            .getCurrentScene()
            .getEntity(id);
    };
}
