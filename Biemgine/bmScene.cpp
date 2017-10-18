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

void bmScene::created()
{
    // Update systems
    auto physicsSystem = new bmPhysicsSystem();
    auto oxygenSystem = new bmOxygenSystem();

    oxygenSystem->setTransitionManager(transitionManager);

    systemManager->addSystem(physicsSystem);
    systemManager->addSystem(oxygenSystem);


    // Render systems
    auto gd = getWindow()->getGraphicsDevice();

    auto renderSystem = new bmRenderSystem();
    auto renderOxygenSystem = new bmRenderOxygenSystem();

    renderSystem->setGraphicsDevice(gd);
    renderOxygenSystem->setGraphicsDevice(gd);

    systemManager->addSystem(renderSystem);
    systemManager->addSystem(renderOxygenSystem);

    sceneCreated();
}
