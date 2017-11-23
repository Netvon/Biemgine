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
        TextComponent(string pText = "", Color pColor = { 255, 255, 255, 255 }, float pOffsetX = 0, float pOffsetY = 0, bool pVisible = true, bool center = false, string pTag = "");
        ~TextComponent();

        const string& getText() const;
        void setText(const string& newText, const Color& newColor);
        const Color& getColor() const;
        void setColor(const Color newColor);

        Size getTextSize() const;
        void setTextSize(const Size& pTextSize);

        float getOffsetX() const;
        float getOffsetY() const;
        bool isVisible() const;
        void setVisible(bool pVisible);
        bool isCenter() const;

        void setTag(const string& tag);
        const string& getTag() const;

    private:
        string text;
        Size textSize;
        Color color;
        float offsetX;
        float offsetY;
        bool visible;
        bool center;
        string tag;
    };
}
