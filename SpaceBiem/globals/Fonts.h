#pragma once

#include "Biemgine.h"

using biemgine::Font;

namespace spacebiem
{
    class Fonts
    {
    public:
        static Font Roboto(int size = 20) {
            return {
                "Roboto-Regular",
                size
            };
        }

        static Font Consolas(int size = 20) {
            return {
                "Consolas",
                size
            };
        }
    };
}
