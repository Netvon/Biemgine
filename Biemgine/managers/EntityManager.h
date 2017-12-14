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
        int addEntity(TArgs&&... arguments);

        inline void updateEntities(std::shared_ptr<SystemManager> manager);
        inline void updateEntities(std::shared_ptr<SystemManager> manager, const float deltaTime);

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
        std::shared_ptr<CameraComponent> camera;
        std::shared_ptr<SystemManager> systemManager;
    };

    template<class TEntity, typename ...TArgs>
    int EntityManager::addEntity(TArgs && ...arguments)
    {
        entities.emplace_back(new TEntity(std::forward<TArgs>(arguments)...));

        Entity* entity = entities.back();
        systemManager->onAddEntity(*entity);

        entity->calculateBounds();
        entity->checkOCCheckable();

        if (!camera && entity->hasComponent("camera")) {
             camera = entity->getComponent<CameraComponent>("camera");
        }

        return entity->getId();
    }
}
