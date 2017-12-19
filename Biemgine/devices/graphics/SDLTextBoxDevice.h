#pragma once

#include "TextBoxDevice.h"
#include <map>

using std::string;

namespace biemgine
{
    class SDLTextBoxDevice :
        public TextBoxDevice
    {
    public:
        SDLTextBoxDevice();
        ~SDLTextBoxDevice();

        void drawTextBox() override;
    };
}
