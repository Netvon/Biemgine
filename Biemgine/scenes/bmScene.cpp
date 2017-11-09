#include "stdafx.h"
#include "bmScene.h"

#include "..\systems\physics\bmPhysicsSystem.h"
#include "..\systems\bmRenderSystem.h"

//#include "..\systems\bmgravitysystem.h"
//#include "..\systems\bmphysicssystem.h"
//#include "..\systems\bmrendersystem.h"
//#include "..\systems\bmoxygenuisystem.h"
//#include "..\systems\bmoxygensystem.h"
//#include "..\systems\bmjumpsystem.h"
//#include "..\systems\bmmovementsystem.h"

namespace biemgine
{
    bmScene::bmScene(bmStateManager & manager)
        : stateManager(&manager) {}

    bmScene::~bmScene()
    {
        systemManager->onSceneSwitch();

        /*delete systemManager;
        delete entityManager;*/
    }

    void bmScene::init() {}

    void bmScene::updateEntities()
    {
        entityManager->updateEntities(systemManager);
    }

    void bmScene::updateEntities(const float deltaTime)
    {
        entityManager->updateEntities(systemManager, deltaTime);
    }

    bmStateManager & bmScene::getTransitionManager() const {
        return *stateManager;
    }

    /*std::shared_ptr<bmEntityManager> bmScene::getEntityManager() const {
        return entityManager;
    }

    std::shared_ptr<bmSystemManager> bmScene::getSystemManager() const {
        return systemManager;
    }*/

    int bmScene::addEntity(bmEntity * entity)
    {
        return entityManager->addEntity(entity);
    }

    std::vector<bmEntity*> bmScene::getEntities() const
    {
        return entityManager->getEntities();
    }

    void bmScene::sceneEnd() {}

    void bmScene::enablePhysics()
    {
        auto physicsSystem = new bmPhysicsSystem();
        systemManager->addSystem(physicsSystem);
        physicsSystem->setTransitionManager(stateManager);
    }

    void bmScene::enableRendering()
    {
        // TODO default rendering device
        auto gd = getWindow()->getGraphicsDevice();
        auto renderSystem = new bmRenderSystem();
        renderSystem->setGraphicsDevice(gd);

        systemManager->addSystem(renderSystem);
        renderSystem->setTransitionManager(stateManager);
    }

    void bmScene::input() { }

    void bmScene::render(float deltaTime) { }
}
