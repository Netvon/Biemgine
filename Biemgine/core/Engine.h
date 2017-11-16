#pragma once

#include "dlldef.h"
#include "..\managers\SceneManager.h"

namespace biemgine
{
    class BIEMGINE Engine
    {
    public:
        template<class TScene>
        void start(const string& windowTitle);
    private:
        SceneManager manager;
    };

    template<class TScene>
    void Engine::start(const string& windowTitle)
    {
        Window window(
            windowTitle,
            1366, 768
        );

        manager.createStateManager(window);
        //manager.changeScene(Scene_menu);
        manager.navigateTo<TScene>();


        while (true) {

            // The engine should keep running until there is no next scene.
            if (!manager.checkNextScene()) break;
        }
    }
}

