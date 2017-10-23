#include "stdafx.h"
#include "bmScene.h"

#include "bmGravitySystem.h"
#include "bmPhysicsSystem.h"
#include "bmRenderSystem.h"
#include "bmOxygenUISystem.h"
#include "bmOxygenSystem.h"

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
    auto gravitySystem = new bmGravitySystem();
    auto physicsSystem = new bmPhysicsSystem();
    auto oxygenSystem = new bmOxygenSystem();
    auto scoreSystem = new bmScoreSystem();
    auto scoreUISystem = new bmScoreUISystem();

    systemManager->addSystem(gravitySystem);
    systemManager->addSystem(physicsSystem);
    systemManager->addSystem(oxygenSystem);
    systemManager->addSystem(scoreSystem);
    systemManager->addSystem(scoreUISystem);


    // Render systems
    auto gd = getWindow()->getGraphicsDevice();

    auto renderSystem = new bmRenderSystem();
    auto oxygenUISystem = new bmOxygenUISystem();

    renderSystem->setGraphicsDevice(gd);
    oxygenUISystem->setGraphicsDevice(gd);

    systemManager->addSystem(renderSystem);
    systemManager->addSystem(oxygenUISystem);

    gravitySystem->setTransitionManager(transitionManager);
    oxygenSystem->setTransitionManager(transitionManager);
    physicsSystem->setTransitionManager(transitionManager);
    renderSystem->setTransitionManager(transitionManager);
    oxygenUISystem->setTransitionManager(transitionManager);


    sceneCreated();
}
