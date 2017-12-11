#pragma once

#include "dlldef.h"
#include <typeindex>

namespace biemgine
{
    class BIEMGINE Component
    {
    public:
        Component();
        virtual ~Component();

        const std::type_index type() {
            return std::type_index(typeid(this));
        }
    };
}
