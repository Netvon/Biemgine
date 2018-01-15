#include "stdafx.h"
#include "Scene.h"

#include "..\systems\physics\PhysicsSystem.h"
#include "..\systems\RenderSystem.h"
#include "..\systems\UISystem.h"
#include "..\systems\ScriptSystem.h"
#include "..\systems\CameraSystem.h"
#include "..\systems\AnimateSystem.h"

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
        : stateManager(&manager), systemManager(std::make_shared<SystemManager>())
    {
        entityManager = std::make_shared<EntityManager>(systemManager);
    }

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
    
    void Scene::sceneEnd() {}

    void Scene::enablePhysics()
    {
        addSystem<PhysicsSystem>();
    }

    void Scene::enableUI()
    {
        addSystem<UISystem>(2);
    }

    void Scene::enableScripts()
    {
        addSystem<ScriptSystem>(2);
    }

    void Scene::enableCamera()
    {
        addSystem<CameraSystem>();
    }

    void Scene::enableAnimations()
    {
        addSystem<AnimateSystem>();
    }

    void Scene::enableRendering()
    {
        // TODO default rendering device
        auto gd = getWindow()->getGraphicsDevice();
        auto renderSystem = new RenderSystem();
        renderSystem->setTimeout(0);
        renderSystem->setGraphicsDevice(gd);

        systemManager->addSystem(renderSystem);
        renderSystem->setStateManager(stateManager);
    }

    void Scene::input() { }

    void Scene::render(float deltaTime) { }

    void Scene::firstFrame()
    {
        //entityManager->addEntitiesToSystems();
    }
    
    Entity * Scene::getEntity(int id) const
    {
        return entityManager->getEntity(id);
    }
}
