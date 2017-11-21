#include "stdafx.h"
#include "SceneManager.h"

using std::pair;

namespace biemgine
{
    void SceneManager::createStateManager(const Window& window)
    {
        currentWindow = &window;
        stateManager = std::make_shared<StateManager>(*this, window);
    }

    bool SceneManager::checkNextScene()
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

    SceneManager::SceneManager() {}

    SceneManager::~SceneManager()
    {
        /*if (nextScene != nullptr)
            delete nextScene;*/

        //currentScene = nullptr;
        //delete stateManager;
    }

    std::shared_ptr<StateManager> SceneManager::getStateManager() {
        return stateManager;
    }

    vector<Entity*> SceneManager::getCurrentSceneEntities() const
    {
        return currentScene->getEntities();
    }

    Entity * SceneManager::getCurrentSceneEntity(int id) const
    {
        return currentScene->getEntity(id);
    }
}
