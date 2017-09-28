#include "stdafx.h"
#include "bmEntityManager.h"

void bmEntityManager::AddEntity(bmEntity* entity)
{

	entities.push_back(entity);

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
