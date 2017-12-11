#pragma once

#include "Biemgine.h"

using biemgine::Color;

namespace spacebiem
{
    class Colors
    {
    public:
        static Color EarthAtmosphere() {
            return Color{ 71, 166, 245, 255 };
        }

        static Color MoonAtmosphere() {
            return Color::White();
        }

        static Color SandAtmosphere() {
            return Color{ 213, 207, 105, 255 };
        }

        static Color ToxicAtmosphere() {
            return Color{ 20, 221, 53, 255 };
        }
        static Color IceAtmosphere() {
            return Color{ 198, 242, 238, 255 };
        }
        static Color LavaAtmosphere() {
            return Color{ 163, 33, 7, 255 };
        }
    };
}
