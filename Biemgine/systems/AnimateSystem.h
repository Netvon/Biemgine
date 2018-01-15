#pragma once
#include "System.h"
#include "..\components\AnimationComponent.h"

namespace biemgine
{
    class AnimateSystem
        : public System
    {
    public:
        struct AnimateEntry
        {
            Entity* entity;
            std::shared_ptr<AnimationComponent> animateComponent;
        };

        void onAddEntity(Entity & entity) override;
        void update(const float deltaTime) override;

    private:
        vector<AnimateEntry> animateEntries;
    };
}
