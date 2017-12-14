#include "stdafx.h"
#include "CameraSystem.h"




namespace biemgine
{
    void CameraSystem::onAddEntity(Entity & pEntity)
    {
        auto camera = pEntity.getComponent<CameraComponent>("camera");

        if (camera != nullptr)
        {
            auto pc = pEntity.getComponent<PositionComponent>("position");

            CSEntity csEntity;
            csEntity.positionComponent = pc;
            csEntity.cameraComponent = camera;
            csEntity.entity = &pEntity;
             
            entities.push_back(csEntity);
        }
    }

    void CameraSystem::update(const Entity & entity)
    {
        for (auto s : entities)
        {
            s.cameraComponent->setWindowWidth(getStateManager()->getWindowWidth());
            s.cameraComponent->setWindowHeight(getStateManager()->getWindowHeight());

            s.cameraComponent->setOriginX(s.positionComponent->getOriginX());
            s.cameraComponent->setOriginY(s.positionComponent->getOriginY());

            int xDelta = static_cast<int>((s.cameraComponent->getWindowWidth()) / 2 - static_cast<int>(s.positionComponent->getOriginX()));
            int yDelta = static_cast<int>((s.cameraComponent->getWindowHeight()) / 2 - static_cast<int>(s.positionComponent->getOriginY()));

            s.cameraComponent->setDeltaX(static_cast<float>(xDelta));
            s.cameraComponent->setDeltaY(static_cast<float>(yDelta));
        }
    }
}
