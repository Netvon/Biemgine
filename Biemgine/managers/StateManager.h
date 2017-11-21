#pragma once

#include "dlldef.h"
#include "..\core\Window.h"
#include "InputManager.h"
#include "..\entities\Entity.h"

using std::string;

namespace biemgine
{
    class SceneManager;

    class BIEMGINE StateManager
    {
    public:
        StateManager(
            SceneManager& pSceneManager,
            const Window& pWindow
        ) : sceneManager(&pSceneManager), window(&pWindow) {};

        ~StateManager();

        int getWindowWidth() const;
        int getWindowHeight() const;

        void pauseGame();
        void resumeGame();
        bool isPaused();

        void drawOverlay();
        void drawBackground(const string& backgroundPath);

        void setInputManager(const InputManager* manager) {
            inputManager = manager;
        }

        const InputManager* getInputManager() const
        {
            return inputManager;
        }

        template<class TScene, typename... TParams>
        void navigateTo(TParams&&... arguments);

        Entity * getEntity(int id) const;

        SceneManager & getSceneManager() const;

    private:
        SceneManager* sceneManager = nullptr;
        const InputManager* inputManager = nullptr;
        const Window* window = nullptr;

        bool paused = false;
    };

    template<class TScene, typename... TParams>
    void StateManager::navigateTo(TParams&&... arguments)
    {
        sceneManager->navigateTo<TScene>(std::forward<TParams>(arguments)...);
    }
}
