#pragma once

#include "dlldef.h"
#include <string>
#include "Component.h"

namespace biemgine
{
    class BIEMGINE TextureComponent :
        public Component
    {
    public:
        TextureComponent(std::string path, float offsetX, float offsetY, int w = -1, int h = -1, unsigned int layer = 0);
        ~TextureComponent();

        const std::string& getPath();
        int getWidth() const;
        int getHeight() const;
        float getOffsetX() const;
        float getOffsetY() const;
        unsigned int getLayer() const;

    private:
        std::string path;
        int width, height;
        float offsetX, offsetY;
        unsigned int layer;
    };
}
