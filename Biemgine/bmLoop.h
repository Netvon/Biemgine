#pragma once

#include "Window.h"
#include "bmInputManager.h"
#include <vector>

class bmLoop
{
public:

    bmInputManager im;

    virtual ~bmLoop() {};

    void start(const Window * window);
    void signalQuit();

    const Window* getWindow() const {
        return window;
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



