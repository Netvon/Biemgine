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

        template<class TScene, typename... TParams>
        void navigateTo(TParams&&... arguments);

        Scene & getCurrentScene() const;

    private:
        std::unique_ptr<Scene> currentScene{ nullptr };
        const Window* currentWindow;
        std::shared_ptr<StateManager> stateManager{ nullptr };

        std::unique_ptr<Scene> nextScene{ nullptr };

        //int nextScene;
    };

    template<class TScene, typename... TParams>
    void SceneManager::navigateTo(TParams&&... arguments)
    {
        nextScene = std::make_unique<TScene>(*stateManager, std::forward<TParams>(arguments)...);

        if (currentScene != nullptr)
            currentScene->signalQuit();
    }
}
