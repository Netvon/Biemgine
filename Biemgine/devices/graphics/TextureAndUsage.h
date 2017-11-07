#pragma once
#include "stdafx.h"

namespace biemgine {
    struct TextureAndUsage {
        SDL_Texture* texture;
        int usageCount = 0;

    };
}
