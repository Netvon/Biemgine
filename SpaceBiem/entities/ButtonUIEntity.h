#pragma once

#include "stdafx.h"
#include "Biemgine.h"

using std::string;
using biemgine::Entity;
using biemgine::Color;
using biemgine::StateManager;

namespace spacebiem
{
    class ButtonUIEntity :
        public Entity
    {
    public:
        ButtonUIEntity(float x, float y, Color color, float w, float h, const string& pText, std::function<void(StateManager*)> onClick);
    };
}
