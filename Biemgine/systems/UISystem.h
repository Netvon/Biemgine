#pragma once
#include "System.h"
#include "..\entities\Entity.h"

namespace biemgine
{
    class UISystem
        : public System
    {
    public:
        UISystem();

        void before(const float deltaTime) override;
        void update(const Entity& entity, const float deltaTime) override;
    private:
        Point currentMouseLocation;
        bool isLeftMouseDown = false;
        bool sceneWasSwitched = false;
        float clickCoolDown = 0.5f;
    };
}
