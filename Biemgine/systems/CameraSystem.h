#pragma once
#include "System.h"
#include "../components/PositionComponent.h"
#include "..\components\CameraComponent.h"
#include "..\entities\Entity.h"

namespace biemgine
{
    struct CameraEntry {
        Entity* entity;
        std::shared_ptr<CameraComponent> cameraComponent;
        std::shared_ptr<PositionComponent> positionComponent;
    };

    struct Entry
    {
        Entity* entity;
        std::shared_ptr<PositionComponent> positionComponent;
    };

    class CameraSystem
        : public System
    {
    public:
        ~CameraSystem() {};

        void onAddEntity(Entity& entity);
        void update() override;
        bool isOnScreen(const Entry & e);

    private:
        CameraEntry cameraEntity;
        std::vector<Entry> allEntities;
    };
}
