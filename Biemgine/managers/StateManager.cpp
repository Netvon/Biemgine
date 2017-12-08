#include "stdafx.h"
#include "StateManager.h"
#include "SceneManager.h"
#include "..\devices\audio\SDLAudioDevice.h"

namespace biemgine
{
    StateManager::StateManager(
        SceneManager& pSceneManager,
        const Window& pWindow
    ) : sceneManager(&pSceneManager), window(&pWindow), audioDevice(new SDLAudioDevice()) {};

    StateManager::~StateManager()
    {
        delete audioDevice;
    }

    int StateManager::getWindowWidth() const
    {
        return window->getRenderWidth();
    }

    int StateManager::getWindowHeight() const
    {
        return window->getRenderHeight();
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
            .getCurrentSceneEntity(id);
    }
}
