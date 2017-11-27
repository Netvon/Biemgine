#pragma once

#include "dlldef.h"
#include "..\..\primitives\Primitives.h"
#include "TextureFlip.h"
#include <string>

using std::string;

namespace biemgine
{
    class BIEMGINE GraphicsDevice
    {
    public:
        virtual ~GraphicsDevice() { }
        virtual void drawSquare(int x, int y, int w, int h, Color color, float angle = 0) const = 0;
        virtual void drawTexture(const string& path, int x, int y, int w = -1, int h = -1, float angle = 0, Color color = { 255, 255, 255 }, TextureFlip flip = NONE, bool useCenterAsOrigin = false, SizeRect source = SizeRect::empty()) = 0;
        virtual Size drawText(const Font& pFont, const string& text, int x, int y, Color color, int ptSize, TextureFlip flip = NONE, bool center = false) = 0;

        virtual void clear() const = 0;
        virtual void present() = 0;
    };
}
