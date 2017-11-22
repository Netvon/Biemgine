#pragma once

#include "dlldef.h"
#include <string>
#include "Component.h"
#include "primitives\Primitives.h"
#include "devices\graphics\TextureFlip.h"

using std::string;

namespace biemgine
{
    class BIEMGINE TextureComponent :
        public Component
    {
    public:
        TextureComponent(
            string path,
            float offsetX, float offsetY, int w = -1, int h = -1,
            unsigned int layer = 0, bool pVisible = true,
            const string pTag = "",
            Color color = Color::White(),
            float rotation = 0.0f
        );
        ~TextureComponent();

        const string& getPath();
        int getWidth() const;
        int getHeight() const;
        int getOriginalWidth() const;
        int getOriginalHeight() const;
        void setWidth(int w);
        void setHeight(int h);
        float getOffsetX() const;
        float getOffsetY() const;
        void setOffsetX(int x);
        void setOffsetY(int y);
        unsigned int getLayer() const;

        const string & getTag() const;
        bool isVisible() const;
        void setVisible(bool pVisible);
        void setColor(Color pColor);
        Color getColor() const;
        Color getOriginalColor() const;
        void setRotation(float r);
        float getRotation() const;
        void setFlip(TextureFlip pFlip);
        TextureFlip getFlip();


    private:
        string path;
        int width, height;
        int originalWidth, originalHeight;
        float offsetX, offsetY;
        unsigned int layer;
        const string tag;
        bool visible;
        Color color;
        Color originalColor;
        float rotation;
        TextureFlip flip = TextureFlip::NONE;
    };
}
