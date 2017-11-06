#pragma once

#include "bmComponent.h"
#include <String>

namespace components
{
    class bmTextComponent :
        public bmComponent
    {
    public:
        bmTextComponent(std::string pText = "") : text{ pText } {};

        std::string getText() const {
            return text;
        };

        void setText(std::string newText) {
            text = newText;
        };

    private:
        std::string text;
    };
}
