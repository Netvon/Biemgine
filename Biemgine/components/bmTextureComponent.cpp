#include "bmTextComponent.h"
#include "bmTextureComponent.h"

namespace biemgine {
    bmTextureComponent::bmTextureComponent(std::string path, float offsetX, float offsetY, int w, int h, unsigned int layer)
        : path(path), offsetX(offsetX), offsetY(offsetY), width(w), height(h), layer(layer) { };

    bmTextureComponent::~bmTextureComponent() {}

    const std::string & bmTextureComponent::getPath() {
        return path;
    }

    int bmTextureComponent::getWidth() const {
        return width;
    }

    int bmTextureComponent::getHeight() const {
        return height;
    }

    float bmTextureComponent::getOffsetX() const {
        return offsetX;
    }

    float bmTextureComponent::getOffsetY() const {
        return offsetY;
    }

    unsigned int bmTextureComponent::getLayer() const {
        return layer;
    }
}
