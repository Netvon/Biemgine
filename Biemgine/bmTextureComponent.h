#pragma once
#include "bmComponent.h"
class bmTextureComponent :
    public bmComponent
{
public:
    bmTextureComponent(std::string path, int w = -1, int h = -1) : path(path), width(w), height(h) { };

    std::string& getPath() { return path; };

    int getWidth() const {
        return width;
    }

    int getHeight() const {
        return height;
    }

private:
    std::string path;
    int width, height;
};

