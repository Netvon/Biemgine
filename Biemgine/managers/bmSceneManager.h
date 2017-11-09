#pragma once
#include "dlldef.h"
#include "../scenes/bmScene.h"
#include "bmStateManager.h"
#include <map>
#include <vector>
#include <memory>

using std::map;
using std::string;

namespace biemgine
{
    class BIEMGINE bmSceneManager
    {
    public:
        void createStateManager(const Window& window);
        bool checkNextScene();

        bmSceneManager();
        ~bmSceneManager();

        std::shared_ptr<bmStateManager> getStateManager();

        template<class TScene>
        void navigateTo(const string& parameter = "");

    private:
        std::unique_ptr<bmScene> currentScene{ nullptr };
        const Window* currentWindow;
        std::shared_ptr<bmStateManager> stateManager{ nullptr };

        std::unique_ptr<bmScene> nextScene{ nullptr };

        //int nextScene;
    };

    template<class TScene>
    void bmSceneManager::navigateTo(const string & parameter)
    {
        nextScene = std::make_unique<TScene>(*stateManager);

        if (currentScene != nullptr)
            currentScene->signalQuit();
    }
}
