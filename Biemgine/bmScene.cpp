#include "stdafx.h"
#include "bmScene.h"


void bmScene::updateEntities()
{
	entityManager->updateEntities(systemManager);
}

void bmScene::updateEntities(const float deltaTime)
{
    entityManager->updateEntities(systemManager, deltaTime);
}
