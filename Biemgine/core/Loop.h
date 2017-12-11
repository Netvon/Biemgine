#pragma once

#include "dlldef.h"
#include "../managers/InputManager.h"
#include "Window.h"
#include <vector>

namespace biemgine
{
    class BIEMGINE Loop
    {
    public:
        Loop();
        //static const int BM_GAMELOOP_FPS;
        //static const float BM_GAMELOOP_UPDATE_MS;

        InputManager im;

        virtual ~Loop() {};

        void start(const Window * window);
        void signalQuit();

        const Window* getWindow() const {
            return window;
        }

        const InputManager* getInputManager() const {
            return &im;
        }

        int getFPS() const {
            return fps;
        }

        int getFPSModifier() const {
            return fpsModifier;
        }

        void setFPSModifier(int modifier) {
            fpsModifier = modifier;
        }

    private:
        const Window* window;

        bool quit = false;

        const int fps = 60;
        const int modifier = 30;
        int fpsModifier = 0;

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
        virtual void close() { }
    };
}


