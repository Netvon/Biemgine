#pragma once

#include "dlldef.h"
#include "..\core\Loop.h"
#include "..\managers\SystemManager.h"
#include "..\managers\EntityManager.h"
#include "..\managers\StateManager.h"


#include <memory>

class ResourceManager;

namespace biemgine
{
    class BIEMGINE Scene :
        public Loop
    {
    public:
        Scene(StateManager& manager);

        virtual ~Scene();

        void init();

        void updateEntities();
        void updateEntities(const float deltaTime);

        StateManager& getTransitionManager() const;
        std::shared_ptr<EntityManager> getEntityManager() const;
        /*std::shared_ptr<SystemManager> getSystemManager() const;*/

        virtual void sceneEnd();

        void enablePhysics();
        void enableRendering();
        void enableUI();
        void enableScripts();
        void enableCamera();
        void enableAnimations();

        Entity * getEntity(int id) const;

    protected:
        template<class TSystem>
        void addSystem(int timeout = 0);

        int addEntity(Entity* entity);

        template<class TEntity, typename... TArgs>
        int addEntity(TArgs&&... arguments);

        template<class TEntity, typename... TArgs>
        int addEntityExtra(std::function<void(Entity*)> onAdd, TArgs&&... arguments);

    private:
        std::shared_ptr<SystemManager> systemManager = nullptr;
        std::shared_ptr<EntityManager> entityManager = nullptr;

        StateManager* stateManager = nullptr;

        virtual void input() override;
        virtual void update() override = 0;
        virtual void render(float deltaTime) override;
        virtual void firstFrame() override;
        virtual void created() = 0;
    };

    template<class TSystem>
    void Scene::addSystem(int timeout)
    {
        auto system = new TSystem();
        systemManager->addSystem(system);

        system->setStateManager(stateManager);
        system->setTimeout(timeout);
    }

    template<class TEntity, typename ...TArgs>
    int Scene::addEntity(TArgs && ...arguments)
    {
        return entityManager->addEntity<TEntity>(std::forward<TArgs>(arguments)...);
    }

    template<class TEntity, typename ...TArgs>
    int Scene::addEntityExtra(std::function<void(Entity*)> onAdd, TArgs && ...arguments)
    {
        return entityManager->addEntityExtra<TEntity>(onAdd, std::forward<TArgs>(arguments)...);
    }
}
