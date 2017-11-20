#include "stdafx.h"
#include "Scene.h"

#include "..\systems\physics\PhysicsSystem.h"
#include "..\systems\RenderSystem.h"
#include "..\systems\UISystem.h"
#include "..\systems\ScriptSystem.h"

//#include "..\systems\gravitysystem.h"
//#include "..\systems\physicssystem.h"
//#include "..\systems\rendersystem.h"
//#include "..\systems\oxygenuisystem.h"
//#include "..\systems\oxygensystem.h"
//#include "..\systems\jumpsystem.h"
//#include "..\systems\movementsystem.h"

namespace biemgine
{
    Scene::Scene(StateManager & manager)
        : stateManager(&manager) {}

    Scene::~Scene()
    {
        systemManager->onSceneSwitch();

        /*delete systemManager;
        delete entityManager;*/
    }

    void Scene::init() {}

    void Scene::updateEntities()
    {
        entityManager->updateEntities(systemManager);
    }

    void Scene::updateEntities(const float deltaTime)
    {
        entityManager->updateEntities(systemManager, deltaTime);
    }

    StateManager & Scene::getTransitionManager() const {
        return *stateManager;
    }

    std::shared_ptr<EntityManager> Scene::getEntityManager() const {
        return entityManager;
    }

    /*std::shared_ptr<SystemManager> Scene::getSystemManager() const {
        return systemManager;
    }*/

    int Scene::addEntity(Entity * entity)
    {
        return entityManager->addEntity(entity);
    }

    std::vector<Entity*>& Scene::getEntities() const
    {
        return entityManager->getEntities();
    }
    
    void Scene::sceneEnd() {}

    void Scene::enablePhysics()
    {
        auto physicsSystem = new PhysicsSystem();
        systemManager->addSystem(physicsSystem);
        physicsSystem->setStateManager(stateManager);
    }

    void Scene::enableUI()
    {
        auto uisystem = new UISystem();
        systemManager->addSystem(uisystem);
        uisystem->setStateManager(stateManager);
    }

    void Scene::enableScripts()
    {
        auto scriptsystem = new ScriptSystem();
        systemManager->addSystem(scriptsystem);
        scriptsystem->setStateManager(stateManager);
    }

    void Scene::enableRendering()
    {
        // TODO default rendering device
        auto gd = getWindow()->getGraphicsDevice();
        auto renderSystem = new RenderSystem();
        renderSystem->setGraphicsDevice(gd);

        systemManager->addSystem(renderSystem);
        renderSystem->setStateManager(stateManager);
    }

    void Scene::input() { }

    void Scene::render(float deltaTime) { }

    Entity * Scene::getEntity(int id) const
    {
        return entityManager->getEntity(id);
    }
}
