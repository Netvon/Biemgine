#pragma once
#include "dlldef.h"
#include "../devices/graphics/GraphicsDevice.h"
#include <string>

using std::string;

namespace biemgine {

    class BIEMGINE Window
    {
    public:
        Window
        (
            const string& title = "Untitled Window",
            const int32_t& width = 800,
            const int32_t& height = 600
        );

        ~Window();

        int getWidth() const;

        int getHeight() const;

        GraphicsDevice* getGraphicsDevice() const;

    private:
        bool init();
        int initWindow(
            const string& title,
            const int32_t& width,
            const int32_t& height,
            const int32_t& options
        );

        int windowId;
        //SDL_Window* window = nullptr;
        GraphicsDevice* gd = nullptr;
    };
}
