#pragma once
#include "..\..\stdafx.h"

struct TextureAndUsage {
    SDL_Texture* texture;
    int usageCount = 0;

};
