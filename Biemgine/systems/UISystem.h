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

        void before(const float deltaTime);
        void update(const Entity& entity, const float deltaTime);
        void after();
        void after(const float deltaTime);

        void onSceneSwitch();
    private:
        Point currentMouseLocation;
        bool isLeftMouseDown = false;
    };
}
