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

    systemManager->addSystem(physicsSystem);
    systemManager->addSystem(oxygenSystem);


    // Render systems
    auto gd = getWindow()->getGraphicsDevice();

    auto renderSystem = new bmRenderSystem();
    auto oxygenUISystem = new bmOxygenUISystem();

    renderSystem->setGraphicsDevice(gd);
    oxygenUISystem->setGraphicsDevice(gd);

    systemManager->addSystem(renderSystem);
    systemManager->addSystem(oxygenUISystem);


    oxygenSystem->setTransitionManager(transitionManager);
    physicsSystem->setTransitionManager(transitionManager);
    renderSystem->setTransitionManager(transitionManager);
    oxygenUISystem->setTransitionManager(transitionManager);


    sceneCreated();
}
