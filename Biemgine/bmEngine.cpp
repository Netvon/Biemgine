#include "stdafx.h"
#include "bmEngine.h"
#include "Window.h"
#include "bmSceneManager.h"

void bmEngine::start()
{
    Window window(
        "Biem Test 01",
        1366, 768,
        SDL_WINDOW_OPENGL,
        SDL_RENDERER_ACCELERATED
    );

    manager.createStateManager(&window);
    manager.changeScene(bmScene_menu);


    while (true) {

        // The engine should keep running until there is no next scene.
        if (!manager.checkNextScene()) break;

    }
}
