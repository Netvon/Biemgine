#include "stdafx.h"
#include "bmScene.h"

#include "bmGravitySystem.h"
#include "bmPhysicsSystem.h"
#include "bmRenderSystem.h"
#include "bmRenderOxygenSystem.h"
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

    systemManager->addSystem(gravitySystem);
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

    gravitySystem->setTransitionManager(transitionManager);
    oxygenSystem->setTransitionManager(transitionManager);
    physicsSystem->setTransitionManager(transitionManager);
    renderSystem->setTransitionManager(transitionManager);
    renderOxygenSystem->setTransitionManager(transitionManager);


    sceneCreated();
}
