#pragma once

#include "dlldef.h"
#include "..\managers\bmSceneManager.h"

namespace biemgine
{
    class BIEMGINE bmEngine
    {
    public:
        template<class TScene>
        void start(const string& windowTitle);
    private:
        bmSceneManager manager;
    };

    template<class TScene>
    void bmEngine::start(const string& windowTitle)
    {
        Window window(
            windowTitle,
            1366, 768
        );

        manager.createStateManager(window);
        //manager.changeScene(bmScene_menu);
        manager.navigateTo<TScene>("");


        while (true) {

            // The engine should keep running until there is no next scene.
            if (!manager.checkNextScene()) break;
        }
    }
}

