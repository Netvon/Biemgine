#pragma once

#include "../managers/bmInputManager.h"
#include "../stdafx.h"
#include "Window.h"
#include <vector>

namespace core {

    class bmLoop
    {
    public:

        static const int BM_GAMELOOP_FPS;
        static const float BM_GAMELOOP_UPDATE_MS;

        bmInputManager im;

        virtual ~bmLoop() {};

        void start(const Window * window);
        void signalQuit();

        const Window* getWindow() const {
            return window;
        }

        const bmInputManager* getInputManager() const {
            return &im;
        }

    private:
        SDL_Event event;
        const Window* window;

        bool quit = false;

        float previousTime = static_cast<float>(SDL_GetTicks());
        float lagTime = 0.0f;

        void startLoop();
        void pollEvents();

        void globalUpdate();
        void globalRender(const float deltaTime);
        void globalEnd();

        virtual void input() { }
        virtual void update() { }
        virtual void render(const float deltaTime) { }
        virtual void created() { }
        virtual void end() { }
    };
}


