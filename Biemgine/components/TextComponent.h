#pragma once

#include "dlldef.h"
#include "Component.h"
#include <String>

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

    private:
        std::string text;
    };
}
