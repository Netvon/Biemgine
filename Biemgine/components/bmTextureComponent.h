#pragma once

#include <string>

#include "bmComponent.h"

namespace biemgine
{
    class bmTextureComponent :
        public bmComponent
    {
    public:
        bmTextureComponent(std::string path, float offsetX, float offsetY, int w = -1, int h = -1, unsigned int layer = 0)
            : path(path), offsetX(offsetX), offsetY(offsetY), width(w), height(h), layer(layer) { };

        std::string& getPath() { return path; };

        int getWidth() const {
            return width;
        }

        int getHeight() const {
            return height;
        }

        float getOffsetX() const {
            return offsetX;
        }

        float getOffsetY() const {
            return offsetY;
        }

        unsigned int getLayer() const {
            return layer;
        }

    private:
        std::string path;
        int width, height;
        float offsetX, offsetY;
        unsigned int layer;
    };
}
