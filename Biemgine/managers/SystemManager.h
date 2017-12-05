#pragma once
#pragma once

#include "dlldef.h"
#include "..\systems\System.h"
#include "..\entities\Entity.h"

#include <vector>
#include "EntityManager.h"

namespace biemgine
{
    class BIEMGINE SystemManager
    {
    public:

        SystemManager();

        ~SystemManager();

        inline void preUpdate();
        //void preUpdate(const float deltaTime);

        inline void postUpdate();
        inline void postUpdate(const float deltaTime);

        inline void acceptForUpdate(const Entity& entity);
        inline void acceptForUpdate(const Entity& entity, const float deltaTime);

        inline void builtUpdateMap(std::shared_ptr<EntityManager> manger);

        void addSystem(System* system);

        void onSceneSwitch();
    private:
        std::vector<System*> systems;
    };
}
