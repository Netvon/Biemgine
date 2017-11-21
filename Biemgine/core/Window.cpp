#include "stdafx.h"
#include "Window.h"
#include "..\devices\graphics\SDLGraphicsDevice.h"

#include <SDL.h>

namespace biemgine
{
    SDL_Window * getWindow(int id) {
        return SDL_GetWindowFromID(id);
    }

    Window::Window(
        const string & title,
        const int32_t & width,
        const int32_t & height,
        bool maximize)
    {
        if (init()) {

            int id = initWindow(title, width, height, SDL_WINDOW_SHOWN);

            gd = new SDLGraphicsDevice(getWindow(id), maximize);
        }
    }

    Window::~Window()
    {
        if (gd != nullptr) {
            delete gd;
        }

        SDL_DestroyWindow(getWindow(windowId));
        SDL_Quit();
    }

    int Window::getWidth() const
    {
        auto renderer = SDL_GetRenderer(getWindow(windowId));
        int w, h = 0;
        SDL_RenderGetLogicalSize(renderer, &w, &h);

        return w;
    }

    int Window::getHeight() const
    {
        auto renderer = SDL_GetRenderer(getWindow(windowId));
        int w, h = 0;
        SDL_RenderGetLogicalSize(renderer, &w, &h);

        return h;
    }

    GraphicsDevice * Window::getGraphicsDevice() const
    {
        return gd;
    }

    bool Window::init()
    {
        if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        {
            std::cout << "could not initialize SDL2 \n" << SDL_GetError() << "\n";
            return false;
        }

        return true;
    }

    int Window::initWindow(
        const string & title,
        const int32_t & width,
        const int32_t & height,
        const int32_t & options)
    {
        auto w = SDL_CreateWindow(
            (const char*)title.c_str(),
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            width,
            height,
            options
        );

        //SDL_MaximizeWindow(window);

        /*if (SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN) < 0)
            cout << "Failed to Set Fullscreen\n" << SDL_GetError() << endl;*/

        if (w == nullptr) {
            std::cout << "Failed to initialize Window\n" << SDL_GetError() << std::endl;
            return 0;
        }
        else {
            windowId = SDL_GetWindowID(w);
            return windowId;
        }
    }
}
