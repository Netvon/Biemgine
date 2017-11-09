#pragma once

#include "dlldef.h"
#include <string>
#include "bmComponent.h"

namespace biemgine
{
    class BIEMGINE bmTextureComponent :
        public bmComponent
    {
    public:
        bmTextureComponent(std::string path, float offsetX, float offsetY, int w = -1, int h = -1, unsigned int layer = 0);
        ~bmTextureComponent();

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
