#pragma once

#include "dlldef.h"
#include "..\..\primitives\bmPrimitives.h"
#include "TextureFlip.h"
#include <string>

using std::string;

namespace biemgine {
    class BIEMGINE GraphicsDevice
    {
    public:
        virtual ~GraphicsDevice() { }
        virtual void drawSquare(int x, int y, int w, int h, bmColor color, float angle = 0) const = 0;
        virtual void drawTexture(const string& path, int x, int y, int w = -1, int h = -1, float angle = 0, bmColor color = { 255, 255, 255 }, TextureFlip flip = NONE) = 0;
        virtual void drawText(const string& text, int x, int y, bmColor color, int ptSize, TextureFlip flip = NONE) = 0;

        virtual void clear() const = 0;
        virtual void present() = 0;
    };
}
