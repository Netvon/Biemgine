#pragma once

#include "dlldef.h"
#include "..\managers\SceneManager.h"
#include "..\primitives\Primitives.h"

namespace biemgine
{
    class BIEMGINE Engine
    {
    public:
        template<class TScene>
        void start(const string& windowTitle, Size renderSize, bool maximize);
    private:
        SceneManager manager;
    };

    template<class TScene>
    void Engine::start(const string& windowTitle, Size renderSize, bool maximize)
    {
        Window window(
            windowTitle,
            renderSize.width, renderSize.height,
            maximize
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

