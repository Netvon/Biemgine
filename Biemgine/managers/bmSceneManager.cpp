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
            currentScene = nullptr;
        }

        if (nextScene == nullptr) {
            return false;
        }
        else {

            currentScene = nextScene;
            nextScene = nullptr;

            transitionManager->setInputManager(currentScene->getInputManager());
            currentScene->start(currentWindow);

            return true;
        }
    }

    bmSceneManager::bmSceneManager() {}

    bmSceneManager::~bmSceneManager()
    {
        if (nextScene != nullptr)
            delete nextScene;

        //currentScene = nullptr;
        delete transitionManager;
    }

    bmStateManager * bmSceneManager::getTransitionManager() {
        return transitionManager;
    }
}

