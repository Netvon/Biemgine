#include "SDLTextBoxDevice.h"
#include <SDL.h>

namespace biemgine {

    SDLTextBoxDevice::SDLTextBoxDevice()
    {
    }

    SDLTextBoxDevice::~SDLTextBoxDevice()
    {
    }

    void SDLTextBoxDevice::drawTextBox()
    {
        SDL_StartTextInput();
    }

}
