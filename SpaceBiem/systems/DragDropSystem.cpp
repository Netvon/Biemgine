#include "stdafx.h"
#include "DragDropSystem.h"

namespace spacebiem
{
    void DragDropSystem::onAddEntity(Entity & entity)
    {
        if (entity.isTag("camera")) {
            DragDropEntry entry;
            entry.entity = &entity;
            entry.positionComponent = entity.getComponent<PositionComponent>("position");

            cameraEntity = entry;
        }

        if (entity.isTag("kliko")) {
            DragDropEntry entry;
            entry.entity = &entity;
            entry.positionComponent = entity.getComponent<PositionComponent>("position");

            trashEntity = entry;
        }

        if (!entity.hasComponent("ui") && entity.hasComponent("position")) {

            DragDropEntry entry;
            entry.entity = &entity;
            entry.positionComponent = entity.getComponent<PositionComponent>("position");

            dragDropEntries.push_back(std::move(entry));
        }

    }

    void DragDropSystem::update()
    {
        auto inputManager = getStateManager()->getInputManager();
        float mouseX = inputManager->getMouseLocation().x;
        float mouseY = inputManager->getMouseLocation().y;
        auto cc = cameraEntity.entity->getComponent<CameraComponent>("camera");
        auto pc = cameraEntity.positionComponent;

        // pickup
        if (!dragging && dragEntity == nullptr && inputManager->isLeftMouseDown()) {

            bool pickup = false;

            // First pickup resources
            // prioritise pickup when object was placed or not
            for (DragDropEntry& entry : dragDropEntries)
            {
                if (entry.entity->getTag().find("_placed") != std::string::npos && checkResourcePickup(entry, mouseX, mouseY)) pickup = true;
            }
            if (!pickup) {
                for (DragDropEntry& entry : dragDropEntries)
                {
                    if (entry.entity->getTag().find("_placed") == std::string::npos && checkResourcePickup(entry, mouseX, mouseY)) pickup = true;
                }
            }

            // Then pickup planets / ai / player
            // prioritise pickup when object is placed or not
            if (!pickup) {
                for (DragDropEntry& entry : dragDropEntries)
                {
                    if (entry.entity->getTag().find("_placed") != std::string::npos && checkElsePickup(entry, mouseX, mouseY)) pickup = true;
                }
            }
            if(!pickup){
                for (DragDropEntry& entry : dragDropEntries)
                {
                    if (entry.entity->getTag().find("_placed") == std::string::npos && checkElsePickup(entry, mouseX, mouseY)) pickup = true;
                }
            }
            

            if (pickup) {
                dragEntity->entity->scaleSize(1.03f);
                dragOffsetX *= 1.03f;
                dragOffsetY *= 1.03f;
            }

            dragging = true;
        } // drop
        else if (dragging && !inputManager->isLeftMouseDown()) {

            if (dragEntity != nullptr) {

                bool doDrop = true;

                for (const DragDropEntry& entry : dragDropEntries)
                {
                    // check if object is planet and is dropped over another planet
                }

                if (doDrop) {

                    if (mouseX >= trashEntity.positionComponent.get()->getX() + trashEntity.entity->minX &&
                        mouseX <= trashEntity.positionComponent.get()->getX() + trashEntity.entity->maxX &&
                        mouseY >= trashEntity.positionComponent.get()->getY() + trashEntity.entity->minY &&
                        mouseY <= trashEntity.positionComponent.get()->getY() + trashEntity.entity->maxY) {
                        dragEntity->entity->die();
                    }

                    dragEntity->entity->scaleSize(1/1.03f);
                    dragEntity->entity->calculateBounds();
                    if (dragEntity->entity->getTag().find("_placed") == std::string::npos) {
                        dragEntity->entity->setTag(dragEntity.get()->entity->getTag() + "_placed");

                        dragEntity->positionComponent->setX(dragEntity->positionComponent->getX() - (cc->getWindowWidth() / 2) + pc->getX());
                        dragEntity->positionComponent->setY(dragEntity->positionComponent->getY() - (cc->getWindowHeight() / 2) + pc->getY());

                    }

                    dragEntity = nullptr;

                }
            }

            dragging = false;
        }


        float cameraMovementMargin = 10.f;
        float cameraMovementSpeed = 3.5f;


        if (mouseX < cameraMovementMargin || inputManager->isKeyDown("Left")) pc->setX(pc->getX() - cameraMovementSpeed);
        if (mouseY < cameraMovementMargin || inputManager->isKeyDown("Up")) pc->setY(pc->getY() - cameraMovementSpeed);
        if (mouseX > cc->getWindowWidth() - cameraMovementMargin || inputManager->isKeyDown("Right")) pc->setX(pc->getX() + cameraMovementSpeed);
        if (mouseY > cc->getWindowHeight() - cameraMovementMargin || inputManager->isKeyDown("Down")) pc->setY(pc->getY() + cameraMovementSpeed);


        // dragging
        if (dragging && dragEntity != nullptr) {

            dragEntity->positionComponent->setX(mouseX + dragOffsetX);
            dragEntity->positionComponent->setY(mouseY + dragOffsetY);

        }
    }
    bool DragDropSystem::checkResourcePickup(DragDropEntry & entry, float mouseX, float mouseY)
    {
        auto cc = cameraEntity.entity->getComponent<CameraComponent>("camera");

        float dX = cc->getDeltaX();
        float dY = cc->getDeltaY();

        if (entry.entity->getTag().find("_placed") == std::string::npos) {
            dX = 0.f;
            dY = 0.f;
        }

        // Resources apparently have its x position at its middle point -__-"
        if ((entry.entity->isTag("resource") || entry.entity->isTag("resource_placed")) &&
            mouseX >= entry.positionComponent.get()->getX() + entry.entity->minX - (entry.entity->maxX / 2) + dX &&
            mouseX <= entry.positionComponent.get()->getX() + entry.entity->maxX - (entry.entity->maxX / 2) + dX &&
            mouseY >= entry.positionComponent.get()->getY() + entry.entity->minY + dY &&
            mouseY <= entry.positionComponent.get()->getY() + entry.entity->maxY + dY) {

            dragOffsetX = entry.positionComponent.get()->getX() - mouseX;
            dragOffsetY = entry.positionComponent.get()->getY() - mouseY;

            dragEntity = std::make_shared<DragDropEntry>(entry);
            return true;
        }

        return false;
    }
    bool DragDropSystem::checkElsePickup(DragDropEntry & entry, float mouseX, float mouseY)
    {
        auto cc = cameraEntity.entity->getComponent<CameraComponent>("camera");

        float dX = cc->getDeltaX();
        float dY = cc->getDeltaY();

        if (entry.entity->getTag().find("_placed") == std::string::npos) {
            dX = 0.f;
            dY = 0.f;
        }

        if (!entry.entity->isTag("resource") &&
            mouseX >= entry.positionComponent.get()->getX() + entry.entity->minX + dX &&
            mouseX <= entry.positionComponent.get()->getX() + entry.entity->maxX + dX &&
            mouseY >= entry.positionComponent.get()->getY() + entry.entity->minY + dY &&
            mouseY <= entry.positionComponent.get()->getY() + entry.entity->maxY + dY) {

            dragOffsetX = entry.positionComponent.get()->getX() - mouseX;
            dragOffsetY = entry.positionComponent.get()->getY() - mouseY;

            if (entry.entity->getTag().find("_placed") == std::string::npos) {

                float scale = 1.f;
                if (entry.entity->isTag("ai") || entry.entity->isTag("player")) {
                    scale = 1.0f;
                }
                else {
                    scale = 3.5f;
                }
                entry.entity->scaleSize(scale);
                dragOffsetX *= scale;
                dragOffsetY *= scale;
            }

            dragEntity = std::make_shared<DragDropEntry>(entry);
            return true;
        }

        return false;
    }
}
