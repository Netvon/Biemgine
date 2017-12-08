#pragma once
#include "System.h"
#include "..\components\CameraComponent.h"
#include "..\entities\Entity.h"

namespace biemgine
{
    class CameraSystem
        : public System
    {
    public:
        ~CameraSystem() {};

        void update(const Entity& entity) override;

    private:
        std::shared_ptr<CameraComponent> camera = nullptr;

        // Inherited via System
        virtual required_components requirements() const override;
    };
}
