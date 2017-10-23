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
    auto scoreSystem = new bmScoreSystem();
    auto scoreUISystem = new bmScoreUISystem();

    systemManager->addSystem(physicsSystem);
    systemManager->addSystem(oxygenSystem);
    systemManager->addSystem(scoreSystem);
    systemManager->addSystem(scoreUISystem);


    // Render systems
    auto gd = getWindow()->getGraphicsDevice();

    auto renderSystem = new bmRenderSystem();
    auto renderOxygenSystem = new bmRenderOxygenSystem();

    renderSystem->setGraphicsDevice(gd);
    renderOxygenSystem->setGraphicsDevice(gd);

    systemManager->addSystem(renderSystem);
    systemManager->addSystem(renderOxygenSystem);


    oxygenSystem->setTransitionManager(transitionManager);
    physicsSystem->setTransitionManager(transitionManager);
    renderSystem->setTransitionManager(transitionManager);
    renderOxygenSystem->setTransitionManager(transitionManager);


    sceneCreated();
}
