#pragma once

#include "Biemgine.h"

using biemgine::System;
using biemgine::Entity;
using biemgine::PositionComponent;
using biemgine::TextureComponent;
using biemgine::CameraComponent;

namespace spacebiem
{
    class DragDropSystem :
        public System
    {
    public:
        struct DragDropEntry
        {
            Entity* entity;
            std::shared_ptr<PositionComponent> positionComponent;
        };

        void onAddEntity(Entity& entity) override;
        void update() override;

    private:
        vector<DragDropEntry> dragDropEntries;

        // drag mode or not
        bool dragging = false;

        // the entity that gets dragged
        std::shared_ptr<DragDropEntry> dragEntity = nullptr;

        // the point where the entity gets dragged
        float dragOffsetX;
        float dragOffsetY;

        // the point where the entity should return to if it is dropped in the menu
        float lastX;
        float lastY;

        float dCameraX = 0.f;
        float dCameraY = 0.f;

        // if the dragged entity is a copy from the menu or not
        bool lastCopy = false;

        DragDropEntry cameraEntity;
        DragDropEntry trashEntity;


        bool checkResourcePickup(DragDropEntry& entry, float mouseX, float mouseY);
        bool checkElsePickup(DragDropEntry& entry, float mouseX, float mouseY);


    };
}
