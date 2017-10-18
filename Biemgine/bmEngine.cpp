#include "stdafx.h"
#include "bmEngine.h"
#include "Window.h"
#include "bmSceneManager.h"

bmEngine::bmEngine()
{
    Window window(
        "Biem Test 01",
        1280, 720,
        SDL_WINDOW_OPENGL,
        SDL_RENDERER_ACCELERATED
    );

    bmSceneManager* manager = new bmSceneManager();

    manager->setWindow(&window);
    manager->changeScene(bmScene_menu);


    while (true) {

        // The engine should keep running until there is no next scene.
        if (!manager->checkNextScene()) break;

    }

    delete manager;

}
