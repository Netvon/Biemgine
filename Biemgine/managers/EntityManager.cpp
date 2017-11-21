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

            if (e->isAlive())
                manager->acceptForUpdate(*e);
        }

        manager->postUpdate();
    }

    void EntityManager::updateEntities(std::shared_ptr<SystemManager> manager, const float deltaTime)
    {
        manager->preUpdate(deltaTime);

        for (Entity * e : entities) {

            if (e->isAlive())
                manager->acceptForUpdate(*e, deltaTime);
        }

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
}
