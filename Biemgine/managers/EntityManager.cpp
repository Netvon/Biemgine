#include "stdafx.h"
#include "EntityManager.h"

namespace biemgine
{
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

    void EntityManager::updateEntities(std::shared_ptr<SystemManager> manager)
    {
        manager->preUpdate();

        for (Entity * e : entities) {
            manager->acceptForUpdate(*e);
        }

        manager->postUpdate();

        removeDeadEntities();
    }

    void EntityManager::updateEntities(std::shared_ptr<SystemManager> manager, const float deltaTime)
    {
        manager->preUpdate(deltaTime);

        for (Entity * e : entities) {
            manager->acceptForUpdate(*e, deltaTime);
        }

        manager->postUpdate(deltaTime);

        removeDeadEntities();
    }

    void EntityManager::removeDeadEntities()
    {
        for (vector<Entity*>::iterator e = entities.begin(); e != entities.end();)
        {
            if (!(*e)->isAlive())
                e = entities.erase(e);
            else
                ++e;
        }
    }



}
