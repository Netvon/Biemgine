#include "TextComponent.h"
#include "TextureComponent.h"

namespace biemgine
{
    TextureComponent::TextureComponent(std::string path, float offsetX, float offsetY, int w, int h, unsigned int layer, bool pVisible, const string pTag)
        : path(path), offsetX(offsetX), offsetY(offsetY), width(w), height(h), layer(layer), visible(pVisible), tag(pTag) {};

    TextureComponent::~TextureComponent() {}

    const std::string & TextureComponent::getPath() {
        return path;
    }

    int TextureComponent::getWidth() const {
        return width;
    }

    int TextureComponent::getHeight() const {
        return height;
    }

    float TextureComponent::getOffsetX() const {
        return offsetX;
    }

    float TextureComponent::getOffsetY() const {
        return offsetY;
    }

    unsigned int TextureComponent::getLayer() const {
        return layer;
    }

    const string & TextureComponent::getTag() const
    {
        return tag;
    }

    bool TextureComponent::isVisible() const
    {
        return visible;
    }

    void TextureComponent::setVisible(bool pVisible)
    {
        visible = pVisible;
    }
}
