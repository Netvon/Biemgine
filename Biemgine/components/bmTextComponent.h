#pragma once

#include "dlldef.h"
#include "bmComponent.h"
#include <String>

namespace biemgine
{
    class BIEMGINE bmTextComponent :
        public bmComponent
    {
    public:
        bmTextComponent(std::string pText = "");
        ~bmTextComponent();

        const std::string& getText() const;
        void setText(const std::string& newText);

    private:
        std::string text;
    };
}
