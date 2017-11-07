#include "stdafx.h"
#include "bmSceneManager.h"

using std::pair;

namespace biemgine {

    void bmSceneManager::createStateManager(const Window& window)
    {
        currentWindow = &window;
        transitionManager = new bmStateManager(*this, window);
    }

    bool bmSceneManager::checkNextScene()
    {
        if (currentScene != nullptr) {
            currentScene->sceneEnd();
            delete currentScene;
        }

        if (nextScene == nullptr) {
            return false;
        }

        currentScene = nextScene;
        nextScene = nullptr;

        transitionManager->setInputManager(currentScene->getInputManager());
        currentScene->start(currentWindow);

        return true;
    }

    bmSceneManager::~bmSceneManager()
    {

    }
}

