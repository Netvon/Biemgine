#include "stdafx.h"
#include "EntityManager.h"

#include <chrono>

namespace biemgine
{
    EntityManager::EntityManager(std::shared_ptr<SystemManager> manager) : systemManager(manager)
    {}

    EntityManager::~EntityManager()
    {
        for (auto it = entities.begin(); it != entities.end(); ++it)
        {
            delete (*it);
        }

        entities.clear();
    }

    int EntityManager::addEntity(Entity* entity)
    {
        entities.push_back(entity);
        return entity->getId();
    }

    inline void EntityManager::updateEntities(std::shared_ptr<SystemManager> manager)
    {
        manager->preUpdate();
        manager->acceptForUpdate();

        manager->postUpdate();
    }

    inline void EntityManager::updateEntities(std::shared_ptr<SystemManager> manager, const float deltaTime)
    {
        manager->preUpdate(deltaTime);
        manager->acceptForUpdate(deltaTime);

        manager->postUpdate(deltaTime); 
    }

    Entity* EntityManager::getEntity(int id) const
    {
        for (auto entity = entities.begin(); entity != entities.end(); ++entity)
        {
            if ((*entity)->getId() == id) return (*entity);
        }

        return nullptr;
    }

    Entity * EntityManager::getEntity(string tag) const
    {
        for (auto entity = entities.begin(); entity != entities.end(); ++entity)
        {
            if ((*entity)->getTag() == tag) return (*entity);
        }

        return nullptr;
    }
}
