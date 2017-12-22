#include "TextComponent.h"
#include "TextureComponent.h"

namespace biemgine
{
    TextureComponent::TextureComponent(std::string path, float offsetX, float offsetY, int w, int h, unsigned int layer, bool pVisible, const string pTag, Color color, float rotation, BLEND_MODE blend)
        : path(path), offsetX(offsetX), offsetY(offsetY), width(w), height(h), originalWidth(w), originalHeight(h), layer(layer), visible(pVisible), tag(pTag), color(color), originalColor(color), rotation(rotation),
            blend(blend) {};

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

    void TextureComponent::setOffsetX(int x) {
        offsetX = x;
    }
    void TextureComponent::setOffsetY(int y) {
        offsetY = y;
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

    Color TextureComponent::getOriginalColor() const
    {
        return originalColor;
    }

    void TextureComponent::setRotation(float r) {
        rotation = r;
    }

    float TextureComponent::getRotation() const {
        return rotation;
    }

    void TextureComponent::setFlip(TextureFlip pFlip) {
        flip = pFlip;
    }
    TextureFlip TextureComponent::getFlip() {
        return flip;
    }

    const SizeRect & TextureComponent::getRect() const
    {
        return SizeRect::empty();
    }

    TextureComponent::BLEND_MODE TextureComponent::getBlendMode() const
    {
        return blend;
    }
}
