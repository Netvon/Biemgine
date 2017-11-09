#pragma once

#include "Biemgine.h"
using biemgine::bmSystem;
using biemgine::bmEntity;

namespace spacebiem
{
    class bmScoreSystem :
        public bmSystem
    {
    public:
        bmScoreSystem();
        ~bmScoreSystem();

        void update(const bmEntity& entity) override;
        void onSceneSwitch() override;
    };
}
