#include "stdafx.h"
#include "Loop.h"

#include <SDL.h>
#include <chrono>

namespace biemgine
{
    const int Loop::BM_GAMELOOP_FPS = 60;
    const float Loop::BM_GAMELOOP_UPDATE_MS = 1000.0f / BM_GAMELOOP_FPS;

    Loop::Loop() :
        previousTime(static_cast<float>(SDL_GetTicks())) {}

    void Loop::start(const Window* pWindow)
    {
        window = pWindow;

        im.setWindow(pWindow);

        created();
        init();
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

            while (lagTime >= BM_GAMELOOP_UPDATE_MS)
            {
                pollEvents();
                globalUpdate();
                lagTime = lagTime - BM_GAMELOOP_UPDATE_MS;
            }

            globalRender(lagTime / BM_GAMELOOP_UPDATE_MS);
        }

        end();
    }

    void Loop::pollEvents()
    {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            quit = event.type == SDL_QUIT;
        }
    }

    void Loop::globalUpdate()
    {
        im.update();
        input();

        auto start = std::chrono::high_resolution_clock::now();
        update();
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> diff = end - start;

        printf("Timed Update took %f s\n", diff.count());
    }

    void Loop::globalRender(const float deltaTime)
    {
        window->getGraphicsDevice()->clear();
        auto start = std::chrono::high_resolution_clock::now();
        render(deltaTime);
        window->getGraphicsDevice()->present();

        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> diff = end - start;

        printf("Render took %f s\n", diff.count());
    }
}

