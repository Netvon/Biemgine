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
        /*std::shared_ptr<EntityManager> getEntityManager() const;
        std::shared_ptr<SystemManager> getSystemManager() const;*/

        std::vector<Entity*> getEntities() const;

        virtual void sceneEnd();

        void enablePhysics();
        void enableRendering();
        void enableUI();

        Entity * getEntity(int id) const;

    protected:
        template<class TSystem>
        void addSystem();

        int addEntity(Entity* entity);

    private:
        std::shared_ptr<SystemManager> systemManager = std::make_shared<SystemManager>();
        std::shared_ptr<EntityManager> entityManager = std::make_shared<EntityManager>();

        StateManager* stateManager = nullptr;

        virtual void input() override;
        virtual void update() override = 0;
        virtual void render(float deltaTime) override;

        virtual void created() = 0;
    };

    template<class TSystem>
    void Scene::addSystem()
    {
        auto system = new TSystem();
        systemManager->addSystem(system);

        system->setStateManager(stateManager);
    }
}
