#pragma once

#include "stdafx.h"
#include <vector>

using std::vector;

#include "Biemgine.h"

using biemgine::System;
using biemgine::Entity;

#include "../entities/AIEntity.h"
#include "../components/AIComponent.h"
#include "../entities/PlayerEntity.h"

namespace spacebiem
{
    class AIMovementSystem :
        public System
    {
    public:
        void after() override;
        void update(const Entity & entity) override;

    private:
        vector<const Entity*> ais;
        vector<const Entity*> players;

        const Entity * findPlayerInRange(const Entity * entity) const;
        Direction computeDirection() const;
        float computeForce() const;
    };
}
