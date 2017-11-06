#include "..\..\stdafx.h"
#include "bmSceneManager.h"

using std::pair;

void bmSceneManager::createStateManager(Window* window)
{
    currentWindow = window;
    transitionManager = new bmStateManager(this, window);
}


void bmSceneManager::changeScene(bmSceneType changingScene)
{
    nextScene = changingScene;

    if (currentScene != nullptr) currentScene->signalQuit();

}

bool bmSceneManager::checkNextScene() 
{

    if (currentScene != nullptr) {
        currentScene->sceneEnd();
        delete currentScene;
    }

    switch (nextScene) {
    case bmScene_level:

        nextScene = bmScene_NULL;

        currentScene = new bmLevelScene(transitionManager);

        break;
    case bmScene_menu:

        nextScene = bmScene_NULL;

        currentScene = new bmMenuScene(transitionManager);

        break;
    default:
        return false;
    }

    transitionManager->setInputManager(currentScene->getInputManager());
    currentScene->start(currentWindow);

    return true;
}

bmSceneManager::~bmSceneManager()
{
    for (pair<const string, const bmScene*> pair : scenes) {
        delete pair.second;
    }

    delete transitionManager;
}

void bmSceneManager::navigateTo(const string & name, const string & parameter)
{
    const bmScene* scene = scenes.at(name);

    if (scene != nullptr) {
        transitionManager->setInputManager(scene->getInputManager());
        currentScene->start(currentWindow);
    }
    else {
        // exception
    }
}

