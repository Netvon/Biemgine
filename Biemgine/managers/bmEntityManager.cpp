#include "stdafx.h"
#include "bmEntityManager.h"

namespace biemgine
{
    bmEntityManager::~bmEntityManager()
    {
        for (auto it = entities.begin(); it != entities.end(); ++it)
        {
            delete (*it);
        }

        entities.clear();
    }

    int bmEntityManager::addEntity(bmEntity* entity)
    {
        entities.push_back(entity);
        return entity->getId();
    }

    void bmEntityManager::updateEntities(std::shared_ptr<bmSystemManager> manager)
    {
        manager->preUpdate();

        for (bmEntity * e : entities) {
            manager->acceptForUpdate(*e);
        }

        manager->postUpdate();
    }

    void bmEntityManager::updateEntities(std::shared_ptr<bmSystemManager> manager, const float deltaTime)
    {
        manager->preUpdate(deltaTime);

        for (bmEntity * e : entities) {
            manager->acceptForUpdate(*e, deltaTime);
        }

        manager->postUpdate(deltaTime);
    }
}
