#include "..\stdafx.h"
#include "bmScene.h"

//#include "..\systems\bmgravitysystem.h"
//#include "..\systems\bmphysicssystem.h"
//#include "..\systems\bmrendersystem.h"
//#include "..\systems\bmoxygenuisystem.h"
//#include "..\systems\bmoxygensystem.h"
//#include "..\systems\bmjumpsystem.h"
//#include "..\systems\bmmovementsystem.h"

bmScene::bmScene()
{

}

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
    //auto gravitySystem = new bmGravitySystem();
    //auto physicsSystem = new bmPhysicsSystem();
    //auto oxygenSystem = new bmOxygenSystem();
    //auto jumpSystem = new bmJumpSystem();
    //auto scoreSystem = new bmScoreSystem();
    //auto scoreUISystem = new bmScoreUISystem();
    //auto movementSystem = new bmMovementSystem();
    //auto oxygenUISystem = new bmOxygenUISystem();

    //systemManager->addSystem(jumpSystem);
    //systemManager->addSystem(gravitySystem);
    //systemManager->addSystem(physicsSystem);
    //systemManager->addSystem(oxygenSystem);
    //systemManager->addSystem(scoreSystem);
    //systemManager->addSystem(scoreUISystem);
    //systemManager->addSystem(movementSystem);
    //systemManager->addSystem(oxygenUISystem);

    //auto gd = getWindow()->getGraphicsDevice();

    //auto renderSystem = new bmRenderSystem();

    //renderSystem->setGraphicsDevice(gd);

    //systemManager->addSystem(renderSystem);

    //gravitySystem->setTransitionManager(transitionManager);
    //oxygenSystem->setTransitionManager(transitionManager);
    //physicsSystem->setTransitionManager(transitionManager);
    //renderSystem->setTransitionManager(transitionManager);
    //oxygenUISystem->setTransitionManager(transitionManager);
    //jumpSystem->setTransitionManager(transitionManager);
    //movementSystem->setTransitionManager(transitionManager);

    //sceneCreated();
}
