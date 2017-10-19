#include "stdafx.h"
#include "bmLoop.h"


const int BM_GAMELOOP_FPS = 60;
const float BM_GAMELOOP_UPDATE_MS = 1000.0f / BM_GAMELOOP_FPS;

void bmLoop::start(const Window* bmwindow)
{
    window = bmwindow;

    created();
    startLoop();
}

void bmLoop::signalQuit()
{
    quit = true;
}

void bmLoop::startLoop()
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

    globalEnd();
    end();
}

void bmLoop::pollEvents()
{
    while (SDL_PollEvent(&event)) {
        quit = event.type == SDL_QUIT;
    }
}


void bmLoop::globalUpdate()
{
    im.update();
    input();

    update();
}

void bmLoop::globalRender(const float deltaTime)
{
    window->getGraphicsDevice()->clear();
    render(deltaTime);
    window->getGraphicsDevice()->present();
}

void bmLoop::globalEnd()
{

}



