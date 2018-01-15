#pragma once
#include "stdafx.h"
#include "dlldef.h"
#include "..\entities\Entity.h"
#include "SystemManager.h"
#include "..\components\CameraComponent.h"
#include "..\components\PositionComponent.h"
#include <vector>
#include <memory>

using std::string;

namespace biemgine
{
    class BIEMGINE EntityManager
    {
    public:
        EntityManager(std::shared_ptr<SystemManager> manager);
        ~EntityManager();
        int addEntity(Entity* entity);

        template<class TEntity, typename...TArgs>
        int addEntityExtra(std::function<void(Entity*)> onAdd, TArgs&&... arguments);

        template<class TEntity, typename...TArgs>
        int addEntity(TArgs&&... arguments);

        inline void updateEntities(std::shared_ptr<SystemManager> manager);
        inline void updateEntities(std::shared_ptr<SystemManager> manager, const float deltaTime);

        auto begin() const {
            return entities.begin();
        }

        auto end() const {
            return entities.end();
        }

        void addEntitiesToSystems();

        Entity* getEntity(int id) const;
        Entity* getEntity(string tag) const;

    private:
        std::vector<Entity*> entities;
        std::shared_ptr<SystemManager> systemManager;
    };

    template<class TEntity, typename ...TArgs>
    int EntityManager::addEntityExtra(std::function<void(Entity*)> onAdd, TArgs && ...arguments)
    {
        entities.emplace_back(new TEntity(std::forward<TArgs>(arguments)...));

        if (onAdd != nullptr) {
            onAdd(entities.back());
        }

        entities.back()->calculateBounds();
        entities.back()->checkOCCheckable();
        systemManager->onAddEntity(*entities.back());

        return entities.back()->getId();
    }

    template<class TEntity, typename ...TArgs>
    int EntityManager::addEntity(TArgs && ...arguments)
    {
        entities.emplace_back(new TEntity(std::forward<TArgs>(arguments)...));

        entities.back()->calculateBounds();
        entities.back()->checkOCCheckable();
        systemManager->onAddEntity(*entities.back());

        return entities.back()->getId();
    }
}
