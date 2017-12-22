#pragma once

#include "dlldef.h"
#include "Component.h"
#include <String>
#include "ColorComponent.h"
#include "..\primitives\Primitives.h"

using std::string;

namespace biemgine
{
    class BIEMGINE TextComponent :
        public Component
    {
    public:
        TextComponent(Font pFont, string pText = "", Color pColor = { 255, 255, 255, 255 }, bool center = false, float pOffsetX = 0, float pOffsetY = 0, unsigned int pLayer = 200u, bool pVisible = true, string pTag = "");
        ~TextComponent();

        const string& getText() const;
        void setText(string newText, Color newColor);
        const Color& getColor() const;
        void setColor(const Color newColor);

        Size getTextSize() const;
        void setTextSize(const Size& pTextSize);

        float getOffsetX() const;
        float getOffsetY() const;
        bool isVisible() const;
        void setVisible(bool pVisible);
        bool isCenter() const;
        unsigned int getLayer() const;

        void setTag(const string& tag);
        const string& getTag() const;

        Font& getFont();

    private:
        string text;
        Size textSize;
        Color color;
        float offsetX;
        float offsetY;
        bool visible;
        bool center;
        string tag;
        Font font;
        unsigned int layer;
    };
}
