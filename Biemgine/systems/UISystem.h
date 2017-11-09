#pragma once
#include "System.h"
#include "..\entities\Entity.h"

namespace biemgine
{
    class UISystem
        : public System
    {
    public:
        ~UISystem();

        void before() override;
        void update(const Entity& entity) override;
    private:
        Point currentMouseLocation;
    };
}
