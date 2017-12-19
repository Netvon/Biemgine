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
            
            for (const DragDropEntry& entry : dragDropEntries)
            {
                if (mouseX >= entry.positionComponent.get()->getX() + entry.entity->minX &&
                    mouseX <= entry.positionComponent.get()->getX() + entry.entity->maxX &&
                    mouseY >= entry.positionComponent.get()->getY() + entry.entity->minY &&
                    mouseY <= entry.positionComponent.get()->getY() + entry.entity->maxY)
                {

                    if (entry.entity->isTag("pick_copy")) {



                    }

                    dragEntity = std::make_shared<DragDropEntry>(entry);
                    dragOffsetX = entry.positionComponent.get()->getX() - mouseX;
                    dragOffsetY = entry.positionComponent.get()->getY() - mouseY;

                    cout << "Picked up Entity!" << endl;

                }
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

                    dragEntity = nullptr;

                }
            }

            dragging = false;
        } // dragging
        else if (dragging && dragEntity != nullptr) {

            dragEntity.get()->positionComponent.get()->setX(mouseX + dragOffsetX);
            dragEntity.get()->positionComponent.get()->setY(mouseY + dragOffsetY);

        }
    }
}
