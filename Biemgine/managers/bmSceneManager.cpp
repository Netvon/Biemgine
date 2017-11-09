#include "stdafx.h"
#include "bmSceneManager.h"

using std::pair;

namespace biemgine
{
    void bmSceneManager::createStateManager(const Window& window)
    {
        currentWindow = &window;
        stateManager = std::make_shared<bmStateManager>(*this, window);
    }

    bool bmSceneManager::checkNextScene()
    {
        if (currentScene != nullptr) {
            currentScene->sceneEnd();
            //delete currentScene;
            currentScene = nullptr;
        }

        if (nextScene == nullptr) {
            return false;
        }
        else {

            currentScene.swap(nextScene);
            //nextScene = nullptr;

            stateManager->setInputManager(currentScene->getInputManager());
            currentScene->start(currentWindow);

            return true;
        }
    }

    bmSceneManager::bmSceneManager() {}

    bmSceneManager::~bmSceneManager()
    {
        /*if (nextScene != nullptr)
            delete nextScene;*/

        //currentScene = nullptr;
        //delete stateManager;
    }

    std::shared_ptr<bmStateManager> bmSceneManager::getStateManager() {
        return stateManager;
    }
}
