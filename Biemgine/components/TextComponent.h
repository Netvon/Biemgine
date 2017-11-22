#pragma once

#include "dlldef.h"
#include "Component.h"
#include <String>
#include "ColorComponent.h"
#include "..\primitives\Primitives.h"

namespace biemgine
{
    class BIEMGINE TextComponent :
        public Component
    {
    public:
        TextComponent(Font pFont, std::string pText = "", Color pColor = { 255, 255, 255, 255 }, float pOffsetX = 0, float pOffsetY = 0, bool pVisible = true, bool center = false);
        ~TextComponent();

        const std::string& getText() const;
        void setText(const std::string& newText, const Color& newColor);
        const Color& getColor() const;
        void setColor(const Color newColor);

        Size getTextSize() const;
        void setTextSize(const Size& pTextSize);

        float getOffsetX() const;
        float getOffsetY() const;
        bool isVisible() const;
        void setVisible(bool pVisible);
        bool isCenter() const;

        Font& getFont();

    private:
        std::string text;
        Size textSize;
        Color color;
        float offsetX;
        float offsetY;
        bool visible;
        bool center;
        Font font;
    };
}
