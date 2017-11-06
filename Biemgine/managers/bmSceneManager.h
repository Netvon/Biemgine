#pragma once
#include "../scenes/bmScene.h"
#include "../scenes/bmSceneType.h"
#include "bmStateManager.h"
#include <map>
#include <vector>

using std::map;
using std::string;

class bmSceneManager
{
public:

    void createStateManager(Window* window);
    bool checkNextScene();

    bmSceneManager() {};
    ~bmSceneManager();

    bmStateManager* getTransitionManager() {
        return transitionManager;
    }

    template<class TScene>
    void navigateTo(const string& parameter = nullptr);

private:
    bmScene* currentScene = nullptr;
    Window* currentWindow;
    bmStateManager* transitionManager;

    bmScene* nextScene = nullptr;

    //int nextScene;
};

template<class TScene>
void bmSceneManager::navigateTo(const string & parameter)
{
    nextScene = new TScene(transitionManager);

    if(currentScene != nullptr)
        currentScene->signalQuit();
}
