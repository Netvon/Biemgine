#pragma once
#include "stdafx.h"
#include <string>
#include "GraphicsDevice.h"

using namespace std;

class Window
{
public:
    Window
    (
        const string& title = "Untitled Window",
        const int32_t& width = 800,
        const int32_t& height = 600,
        const int32_t& options = SDL_WINDOW_SHOWN,
        const int32_t& renderOptions = SDL_RENDERER_ACCELERATED
    );

    ~Window();

    int getWidth() {
        auto renderer = SDL_GetRenderer(window);
        int w, h = 0;
        SDL_RenderGetLogicalSize(renderer, &w, &h);

        return w;
    };

    int getHeight() {
        auto renderer = SDL_GetRenderer(window);
        int w, h = 0;
        SDL_RenderGetLogicalSize(renderer, &w, &h);

        return h;
    };

    GraphicsDevice* getGraphicsDevice() const;

private:
    bool init();
    void initWindow(
        const string& title,
        const int32_t& width,
        const int32_t& height,
        const int32_t& options
    );


    SDL_Window* window = nullptr;

    GraphicsDevice* gd = nullptr;
};

