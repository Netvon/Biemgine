#pragma once

#include "dlldef.h"
#include "..\systems\System.h"
#include "..\entities\Entity.h"
#include <memory>

#include <vector>
#include <algorithm>

namespace biemgine
{
    class BIEMGINE SystemManager
    {
    public:

        template<typename T = Entity>
        struct update {
            typedef std::map<System*, std::vector<T*>> map;
        };

        SystemManager();

        ~SystemManager();

        inline void preUpdate();
        //void preUpdate(const float deltaTime);

        inline void postUpdate();
        inline void postUpdate(const float deltaTime);

        inline void acceptForUpdate(const Entity& entity);
        inline void acceptForUpdate(const Entity& entity, const float deltaTime);

        void updateSystems(float dt = -1, bool usedt = false);

        template<typename TEntityManager, typename TEntity = Entity>
        inline void builtUpdateMap(std::shared_ptr<TEntityManager> manager);

        void addSystem(System* system);

        void onSceneSwitch();
    private:
        std::vector<System*> systems;
        update<>::map update_map;
    };

    template<typename TEntityManager, typename TEntity = Entity>
    inline void SystemManager::builtUpdateMap(std::shared_ptr<TEntityManager> manager)
    {
        std::map<System*, std::vector<TEntity*>> map;
        for (auto system : systems) {

            std::vector<TEntity*> entities;

            auto& requirements = system->requirements();
            auto& requests = system->request_tags();

            for (auto it = manager->begin(); it != manager->end(); ++it)
            {
                TEntity* entity = *it;

                bool hit = entity->meets(requirements);

                if (std::count(requests.begin(), requests.end(), entity->getTag()) > 0) {
                    system->setRequestedEntity(entity->getTag(), entity);
                }

                if (hit) {
                    entities.emplace_back(entity);
                }
            }

            map.emplace(system, entities);
        }

        for (auto it = map.begin(); it != map.end();) {

            auto m = *it;

            if (m.second.empty()) {
                map.erase(it++);
            }
            else {
                ++it;
            }
        }

        update_map = map;
        
    }
}
