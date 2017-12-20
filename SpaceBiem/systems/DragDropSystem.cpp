#include "stdafx.h"
#include "DragDropSystem.h"

namespace spacebiem
{
    void DragDropSystem::onAddEntity(Entity & entity)
    {
        if (entity.isTag("entity_menu")) {
            DragDropEntry entry;
            entry.entity = &entity;
            entry.positionComponent = entity.getComponent<PositionComponent>("position");

            menuEntity = entry;
        }

        if (entity.isTag("entity_trash")) {
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

        // pickup
        if (!dragging && dragEntity == nullptr && inputManager->isLeftMouseDown()) {

            bool pickup = false;

            // First pickup resources
            for (const DragDropEntry& entry : dragDropEntries)
            {
                // Resources apparently have its x position at its middle point -__-"
                if (entry.entity->isTag("resource") &&
                    mouseX >= entry.positionComponent.get()->getX() + entry.entity->minX - (entry.entity->maxX / 2) &&
                    mouseX <= entry.positionComponent.get()->getX() + entry.entity->maxX - (entry.entity->maxX / 2) &&
                    mouseY >= entry.positionComponent.get()->getY() + entry.entity->minY &&
                    mouseY <= entry.positionComponent.get()->getY() + entry.entity->maxY) {

                    dragOffsetX = entry.positionComponent.get()->getX() - mouseX;
                    dragOffsetY = entry.positionComponent.get()->getY() - mouseY;

                    dragEntity = std::make_shared<DragDropEntry>(entry);
                    pickup = true;
                }
            }

            // Then pickup planets
            if (!pickup) {
                for (const DragDropEntry& entry : dragDropEntries)
                {
                    if (!entry.entity->isTag("resource") &&
                        mouseX >= entry.positionComponent.get()->getX() + entry.entity->minX &&
                        mouseX <= entry.positionComponent.get()->getX() + entry.entity->maxX &&
                        mouseY >= entry.positionComponent.get()->getY() + entry.entity->minY &&
                        mouseY <= entry.positionComponent.get()->getY() + entry.entity->maxY) {

                        dragOffsetX = entry.positionComponent.get()->getX() - mouseX;
                        dragOffsetY = entry.positionComponent.get()->getY() - mouseY;

                        if (entry.entity->getTag().find("_placed") == std::string::npos) {
                            entry.entity->scaleSize(2.5f);
                            dragOffsetX *= 2.5f;
                            dragOffsetY *= 2.5f;
                        }

                        dragEntity = std::make_shared<DragDropEntry>(entry);
                        pickup = true;
                    }
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

                }

                if (doDrop) {

                    dragEntity->entity->scaleSize(1/1.03f);
                    dragEntity->entity->calculateBounds();
                    dragEntity->entity->setTag(dragEntity.get()->entity->getTag() + "_placed");
                    dragEntity = nullptr;

                }
            }

            dragging = false;
        }

        // dragging
        if (dragging && dragEntity != nullptr) {

            dragEntity.get()->positionComponent.get()->setX(mouseX + dragOffsetX);
            dragEntity.get()->positionComponent.get()->setY(mouseY + dragOffsetY);

        }
    }
}
