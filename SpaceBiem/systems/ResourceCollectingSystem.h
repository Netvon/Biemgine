#pragma once

#include "biemgine.h"
using biemgine::System;
using biemgine::Entity;
using biemgine::CollidableComponent;

#include "../components/ResourceComponent.h"
#include "../components/ResourceBonusComponent.h"
#include "../components/ScoreBonusComponent.h"
#include "../components/ScoreComponent.h"


namespace spacebiem
{
    class ResourceCollectingSystem : public System
    {
    public:
        void update(const Entity& entity) override;
    };
}
