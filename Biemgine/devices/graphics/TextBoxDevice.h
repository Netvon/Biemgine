#pragma once

#include "dlldef.h"
#include "..\..\primitives\Primitives.h"
#include <string>

using std::string;

namespace biemgine
{
    class BIEMGINE TextBoxDevice
    {
    public:
        virtual ~TextBoxDevice() { }

        virtual void drawTextBox() = 0;
    };
}
