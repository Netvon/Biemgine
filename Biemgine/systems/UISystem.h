#pragma once
#include "System.h"
#include "..\entities\Entity.h"
#include "..\components\UIComponent.h"
#include "..\components\PositionComponent.h"

namespace biemgine
{
    class UISystem
        : public System
    {
    public:
        struct Entry {
            Entity* entity;
            std::shared_ptr<PositionComponent> positionComponent;
            std::shared_ptr<UIComponent> uiComponent;
        };

        UISystem();

        void onAddEntity(Entity & entity) override;
        void before(const float deltaTime) override;
        void update(const float deltaTime) override;

    private:
        vector<Entry> entries;
        Point currentMouseLocation;
        bool isLeftMouseDown = false;
        bool sceneWasSwitched = false;
        float clickCoolDown = 0.5f;
    };
}
