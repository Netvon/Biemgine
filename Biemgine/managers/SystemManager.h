#pragma once
#pragma once

#include "dlldef.h"
#include "..\systems\System.h"
#include "..\entities\Entity.h"

#include <vector>

namespace biemgine
{
    class BIEMGINE SystemManager
    {
    public:

        SystemManager();

        ~SystemManager();

        void preUpdate();
        void preUpdate(const float deltaTime);

        void postUpdate();
        void postUpdate(const float deltaTime);

        void acceptForUpdate(const Entity& entity);
        void acceptForUpdate(const Entity& entity, const float deltaTime);

        void addSystem(System* system);

        void onSceneSwitch();
    private:
        std::vector<System*> systems;
    };
}
