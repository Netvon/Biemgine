#include "stdafx.h"
#include "bmEntityFactory.h"

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

void bmEntityManager::updateEntities(bmSystemManager * manager)
{
    manager->preUpdate();

    for (bmEntity * e : entities) {
        manager->acceptForUpdate(*e);
    }

    manager->postUpdate();
}

void bmEntityManager::updateEntities(bmSystemManager * manager, const float deltaTime)
{
    manager->preUpdate(deltaTime);

    for (bmEntity * e : entities) {
        manager->acceptForUpdate(*e, deltaTime);
    }

    manager->postUpdate(deltaTime);
}
