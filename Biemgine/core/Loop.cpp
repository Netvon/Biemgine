#include "stdafx.h"
#include "Loop.h"

#include <SDL.h>

namespace biemgine
{
    //const int Loop::BM_GAMELOOP_FPS = 60;
    //const float Loop::BM_GAMELOOP_UPDATE_MS = 1000.0f / BM_GAMELOOP_FPS;

    Loop::Loop() :
        previousTime(static_cast<float>(SDL_GetTicks())) {}

    void Loop::start(const Window* pWindow)
    {
        window = pWindow;

        im.setWindow(pWindow);

        created();
        startLoop();
    }

    void Loop::signalQuit()
    {
        quit = true;
    }

    void Loop::startLoop()
    {
        while (!quit) {

            float currentTime = static_cast<float>(SDL_GetTicks());    // Actuele tijd.
            float elapsedTime = currentTime - previousTime;            // Tijd tussen de vorige loop en de actuele tijd.
            previousTime = currentTime;                                // De tijd van de vorige loop de actuele tijd zetten, zodat de volgende loop dat kan gebruiken.
            lagTime += elapsedTime;                                    // Nu dat verschil aan de lagTime toevoegen, zodat we daarmee kunnen beslissen of we alles willen updaten.

            float realFPS = 1000.0f / (fps + (fpsModifier * modifier));

            while (lagTime >= realFPS)
            {
                pollEvents();
                globalUpdate();
                lagTime = lagTime - realFPS;
            }

            // globalRender(lagTime / BM_GAMELOOP_UPDATE_MS);
            globalRender(elapsedTime);

        }

        globalEnd();
        end();
    }

    void Loop::pollEvents()
    {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                close();
                quit = true;
            }
        }
    }

    void Loop::globalUpdate()
    {
        im.update();
        input();

        update();
    }

    void Loop::globalRender(const float deltaTime)
    {
        window->getGraphicsDevice()->clear();
        render(deltaTime);
        window->getGraphicsDevice()->present();
    }

    void Loop::globalEnd()
    {

    }

}

