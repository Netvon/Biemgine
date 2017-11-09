#pragma once

#include "dlldef.h"
#include "..\core\bmLoop.h"
#include "..\managers\bmSystemManager.h"
#include "..\managers\bmEntityManager.h"
#include "..\managers\bmStateManager.h"

#include <memory>

class bmResourceManager;

namespace biemgine
{
    class BIEMGINE bmScene :
        public bmLoop
    {
    public:
        bmScene(bmStateManager& manager);

        virtual ~bmScene();

        void init();

        void updateEntities();
        void updateEntities(const float deltaTime);

        bmStateManager& getTransitionManager() const;
        /*std::shared_ptr<bmEntityManager> getEntityManager() const;
        std::shared_ptr<bmSystemManager> getSystemManager() const;*/

        std::vector<bmEntity*> getEntities() const;

        virtual void sceneEnd();

        void enablePhysics();
        void enableRendering();

    protected:
        template<class TSystem>
        void addSystem();

        int addEntity(bmEntity* entity);

    private:
        std::shared_ptr<bmSystemManager> systemManager = std::make_shared<bmSystemManager>();
        std::shared_ptr<bmEntityManager> entityManager = std::make_shared<bmEntityManager>();

        bmStateManager* stateManager = nullptr;

        virtual void input() override;
        virtual void update() override = 0;
        virtual void render(float deltaTime) override;

        virtual void created() = 0;
    };

    template<class TSystem>
    void bmScene::addSystem()
    {
        auto system = new TSystem();
        systemManager->addSystem(system);

        system->setTransitionManager(stateManager);
    }
}
