#pragma once
#include "bmComponent.h"
class bmTextureComponent :
    public bmComponent
{
public:
    bmTextureComponent(std::string path, float offsetX, float offsetY, int w = -1, int h = -1) : path(path), offsetX(offsetX), offsetY(offsetY), width(w), height(h) { };

    std::string& getPath() { return path; };

    int getWidth() const {
        return width;
    }

    int getHeight() const {
        return height;
    }

    int getOffsetX() const {
        return offsetX;
    }

    int getOffsetY() const {
        return offsetY;
    }

private:
    std::string path;
    int width, height;
    float offsetX, offsetY;
};

