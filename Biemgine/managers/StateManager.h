#pragma once

#include "dlldef.h"
#include "..\core\Window.h"
#include "InputManager.h"
#include "..\entities\Entity.h"

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

        void gameOverTransition();

        void quitLevelTransition();
        void startLevelTransition();

        int getWindowWidth() const;
        int getWindowHeight() const;

        void pauseGame();
        void resumeGame();
        bool isPaused();

        void drawOverlay();
        void drawBackground();

        void setInputManager(const InputManager* manager) {
            inputManager = manager;
        }

        const InputManager* getInputManager() const
        {
            return inputManager;
        }

        template<class TScene>
        void navigateTo();

        Entity * getEntity(int id) const;

        SceneManager & getSceneManager() const;

    private:
        SceneManager* sceneManager = nullptr;
        const InputManager* inputManager = nullptr;
        const Window* window = nullptr;

        bool paused = false;
    };

    template<class TScene>
    void StateManager::navigateTo()
    {
        sceneManager->navigateTo<TScene>("");
    }
}
