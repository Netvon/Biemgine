#pragma once
#include "System.h"
#include "../components/PositionComponent.h"
#include "..\components\CameraComponent.h"
#include "..\entities\Entity.h"

namespace biemgine
{
    struct CSEntity {
        Entity* entity;
        std::shared_ptr<CameraComponent> cameraComponent;
        std::shared_ptr<PositionComponent> positionComponent;
    };

    class CameraSystem
        : public System
    {
    public:
        ~CameraSystem() {};

        void onAddEntity(Entity& entity);
        void update(const Entity& entity) override;

    private:
        std::vector<CSEntity> entities;
    };
}
