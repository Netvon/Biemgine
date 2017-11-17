#include "TextComponent.h"
#include "TextureComponent.h"

namespace biemgine
{
    TextureComponent::TextureComponent(std::string path, float offsetX, float offsetY, int w, int h, unsigned int layer, bool pVisible, const string pTag, Color color)
        : path(path), offsetX(offsetX), offsetY(offsetY), width(w), height(h), originalWidth(w), originalHeight(h), layer(layer), visible(pVisible), tag(pTag), color(color), originalColor(color) {};

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

    int TextureComponent::getOriginalWidth() const {
        return originalWidth;
    }

    int TextureComponent::getOriginalHeight() const {
        return originalHeight;
    }

    void TextureComponent::setWidth(int w) {
        width = w;
    }
    void TextureComponent::setHeight(int h) {
        height = h;
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

    void TextureComponent::setColor(Color pColor) {
        color = pColor;
    }
    Color TextureComponent::getColor() const {
        return color;
    }
    ColorComponent TextureComponent::getOriginalColor() const
    {
        return ColorComponent(originalColor);
    }

}
