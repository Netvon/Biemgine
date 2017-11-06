#pragma once
#include "../scenes/bmScene.h"
#include "../scenes/bmSceneType.h"
#include "bmStateManager.h"
//#include "bmLevelScene.h"
//#include "bmMenuScene.h"
#include <map>
#include <vector>

using std::map;
using std::string;

class bmSceneManager
{
public:

    void createStateManager(Window* window);
    void changeScene(bmSceneType);
    bool checkNextScene();

    bmSceneManager() {};
    ~bmSceneManager();

    bmStateManager* getTransitionManager() {
        return transitionManager;
    }

    template<class TScene>
    void addScene(const string& sceneName);

    void navigateTo(const string& name, const string& parameter = nullptr);

private:
    bmScene* currentScene = nullptr;
    Window* currentWindow;
    bmStateManager* transitionManager;

    std::map<const string, const bmScene*> scenes;

    int nextScene;
};

template<class TScene>
void bmSceneManager::addScene(const string & sceneName)
{
    if (std::is_base_of<bmScene, TScene>) {
        scenes.insert(sceneName, new TScene(transitionManager));
    }
    else {
        // exception
    }
    
}
