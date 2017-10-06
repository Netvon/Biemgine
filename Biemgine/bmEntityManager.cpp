#include "stdafx.h"
#include "bmEntityManager.h"

int bmEntityManager::addEntity(bmEntity* entity)
{
	entities.push_back(entity);
	return entity->getId();
}

void bmEntityManager::clear()
{
	for (auto * entity : entities) {
		entity->clear();
	}

	for (auto it = entities.begin(); it != entities.end(); ++it)
	{
		delete (*it);
	}

	entities.clear();
}

void bmEntityManager::updateEntities(bmSystemManager * manager)
{
	manager->preUpdate();

	for (bmEntity * e : entities) {
		manager->acceptForUpdate(*e);
	}

	manager->postUpdate();
}
