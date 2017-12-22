#pragma once

#include "Biemgine.h"
#include "..\globals\Fonts.h"
#include "..\globals\Ads.h"

using std::string;
using biemgine::Entity;
using biemgine::Color;
using biemgine::PositionComponent;
using biemgine::ColorComponent;
using biemgine::UIComponent;
using biemgine::TextComponent;
using biemgine::TextureComponent;
using biemgine::AnimationComponent;
using biemgine::Point;
using biemgine::Size;
using biemgine::SizeRect;
using biemgine::Font;

namespace spacebiem
{
    class AdEntity :
        public Entity
    {
    public:
        AdEntity();
    };
}
