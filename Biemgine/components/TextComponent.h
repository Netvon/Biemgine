#pragma once

#include "dlldef.h"
#include "Component.h"
#include <String>
#include "ColorComponent.h"

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

    private:
        std::string text;
        Color color;
    };
}
