#include "stdafx.h"
#include "bmScene.h"


void bmScene::updateEntities()
{
	entityManager->updateEntities(systemManager);
}

void bmScene::created()
{
	
}

void bmScene::end()
{
	systemManager->clear();
	delete systemManager;

	entityManager->clear();
	delete entityManager;
}