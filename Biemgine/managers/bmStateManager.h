#pragma once
#include "dlldef.h"
#include "..\core\Window.h"
#include "bmInputManager.h"

namespace biemgine {

    class bmSceneManager;

    class BIEMGINE bmStateManager
    {
    public:
        bmStateManager(
            bmSceneManager& pSceneManager,
            const Window& pWindow
        ) : sceneManager(&pSceneManager), window(&pWindow) {};

        ~bmStateManager();

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

        void setInputManager(const bmInputManager* manager) {
            inputManager = manager;
        }

        const bmInputManager* getInputManager() const
        {
            return inputManager;
        }

        template<class TScene>
        void navigateTo();

    private:
        bmSceneManager* sceneManager = nullptr;
        const bmInputManager* inputManager = nullptr;
        const Window* window = nullptr;

        bool paused = false;
    };

    template<class TScene>
    void bmStateManager::navigateTo()
    {
        sceneManager->navigateTo<TScene>("");
    }
}
