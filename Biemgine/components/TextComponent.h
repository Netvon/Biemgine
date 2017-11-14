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
        TextComponent(std::string pText = "", Color pColor = { 255, 255, 255, 255 });
        ~TextComponent();

        const std::string& getText() const;
        void setText(const std::string& newText, const Color& newColor);
        const Color& getColor() const;
        void setColor(const Color newColor);

        Size getTextSize() const;
        void setTextSize(const Size& pSize);

    private:
        std::string text;
        Size textSize;
        Color color;
    };
}
