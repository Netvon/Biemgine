#pragma once

#include "dlldef.h"
#include "../managers/bmInputManager.h"
#include "Window.h"
#include <vector>

namespace biemgine
{
    class BIEMGINE bmLoop
    {
    public:
        bmLoop();
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
        const Window* window;

        bool quit = false;

        float previousTime;
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


