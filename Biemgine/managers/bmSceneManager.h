#pragma once
#include "../scenes/bmScene.h"
#include "bmStateManager.h"
#include <map>
#include <vector>

using std::map;
using std::string;

namespace biemgine {
    class bmSceneManager
    {
    public:

        void createStateManager(const Window& window);
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
        const Window* currentWindow;
        bmStateManager* transitionManager;

        bmScene* nextScene = nullptr;

        //int nextScene;
    };

    template<class TScene>
    void bmSceneManager::navigateTo(const string & parameter)
    {
        nextScene = new TScene(transitionManager);

        if (currentScene != nullptr)
            currentScene->signalQuit();
    }
}
