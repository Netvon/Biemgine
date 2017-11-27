#pragma once
#include "stdafx.h"
#include "dlldef.h"
#include "..\entities\Entity.h"
#include "SystemManager.h"
#include <vector>
#include <memory>

using std::string;

namespace biemgine
{
    class BIEMGINE EntityManager
    {
    public:
        ~EntityManager();
        int addEntity(Entity* entity);

        template<class TEntity, typename...TArgs>
        int addEntity(TArgs&&... arguments);

        void updateEntities(std::shared_ptr<SystemManager> manager);
        void updateEntities(std::shared_ptr<SystemManager> manager, const float deltaTime);

        auto begin() const {
            return entities.begin();
        }

        auto end() const {
            return entities.end();
        }

        Entity* getEntity(int id) const;
        Entity* getEntity(string tag) const;

    private:
        std::vector<Entity*> entities;
    };

    template<class TEntity, typename ...TArgs>
    int EntityManager::addEntity(TArgs && ...arguments)
    {
        entities.emplace_back(new TEntity(std::forward<TArgs>(arguments)...));
        return entities.back()->getId();
    }
}
