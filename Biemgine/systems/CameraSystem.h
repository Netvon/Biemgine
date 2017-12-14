#pragma once
#include "System.h"
#include "../components/PositionComponent.h"
#include "..\components\CameraComponent.h"
#include "..\entities\Entity.h"

namespace biemgine
{
    struct CameraEntity {
        Entity* entity;
        std::shared_ptr<CameraComponent> cameraComponent;
        std::shared_ptr<PositionComponent> positionComponent;
    };

    struct CSEntity
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
        bool isOnScreen(const CSEntity & e);

    private:
        CameraEntity cameraEntity;
        std::vector<CSEntity> allEntities;
    };
}
