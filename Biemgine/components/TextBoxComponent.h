#pragma once

#include "dlldef.h"
#include "Component.h"
#include <String>
#include "ColorComponent.h"
#include "..\primitives\Primitives.h"

using std::string;

namespace biemgine
{
    class BIEMGINE TextBoxComponent :
        public Component
    {
    public:
        TextBoxComponent();
        ~TextBoxComponent();
    };
}
