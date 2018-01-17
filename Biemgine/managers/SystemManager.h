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

        inline void preUpdate();
        void preUpdate(const float deltaTime);

        inline void postUpdate();
        inline void postUpdate(const float deltaTime);

        inline void acceptForUpdate();
        inline void acceptForUpdate(const float deltaTime);

        void addSystem(System* system);

        void onSceneSwitch();
        void onAddEntity(Entity& entity);
    private:
        std::vector<System*> systems;
    };
}
