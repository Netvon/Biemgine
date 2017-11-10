#pragma once

#include "dlldef.h"
#include "Component.h"
#include <String>
#include "..\primitives\Primitives.h"

namespace biemgine
{
    class BIEMGINE TextComponent :
        public Component
    {
    public:
        TextComponent(std::string pText = "");
        ~TextComponent();

        const std::string& getText() const;
        void setText(const std::string& newText);

        Size getTextSize() const;
        void setTextSize(const Size& pSize);

    private:
        std::string text;
        Size textSize;
    };
}
