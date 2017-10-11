#include "stdafx.h"
#include "bmEntityManager.h"

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
