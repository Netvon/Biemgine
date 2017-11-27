#pragma once

#include "dlldef.h"
#include "..\components\PositionComponent.h"
#include "..\components\ColorComponent.h"
#include "..\components\TextureComponent.h"
#include "..\primitives\Primitives.h"
#include "Entity.h"
#include <functional>

using std::string;
using std::function;

namespace biemgine
{
    class BIEMGINE TextEntity
        : public Entity
    {
    public:
        ~TextEntity();
        TextEntity(Font font, const string& initialValue, Vector position, bool center = true, Color color = Color::White(), function<string()> getValue = nullptr, unsigned int layer = 0);
    };
}
