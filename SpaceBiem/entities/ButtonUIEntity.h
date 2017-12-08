#pragma once

#include "stdafx.h"
#include "Biemgine.h"

using std::string;
using biemgine::Entity;
using biemgine::Color;
using biemgine::StateManager;
using biemgine::Size;

namespace spacebiem
{
    class ButtonUIEntity :
        public Entity
    {
    public:
        ButtonUIEntity(float x, float y, Color buttonColor, Color textcolor, Size size, const string& pText, const string& texturePath, std::function<void(StateManager*)> onClick = nullptr, std::function<void(StateManager*)> onEnter = nullptr, string tag = "");
    };
}
