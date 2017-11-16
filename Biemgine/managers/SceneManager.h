#pragma once
#include "dlldef.h"
#include "../scenes/Scene.h"
#include "StateManager.h"
#include <map>
#include <vector>
#include <memory>

using std::map;
using std::string;

namespace biemgine
{
    class BIEMGINE SceneManager
    {
    public:
        void createStateManager(const Window& window);
        bool checkNextScene();

        SceneManager();
        ~SceneManager();

        std::shared_ptr<StateManager> getStateManager();

        template<class TScene>
        void navigateTo(const string& parameter = "");

        Scene & getCurrentScene() const;

    private:
        std::unique_ptr<Scene> currentScene{ nullptr };
        const Window* currentWindow;
        std::shared_ptr<StateManager> stateManager{ nullptr };

        std::unique_ptr<Scene> nextScene{ nullptr };

        //int nextScene;
    };

    template<class TScene>
    void SceneManager::navigateTo(const string & parameter)
    {
        nextScene = std::make_unique<TScene>(*stateManager);

        if (currentScene != nullptr)
            currentScene->signalQuit();
    }
}
