#include "stdafx.h"
#include "bmScene.h"


void bmScene::updateEntities()
{
	entityManager->updateEntities(systemManager);
}