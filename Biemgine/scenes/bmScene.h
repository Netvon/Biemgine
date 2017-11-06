#pragma once
#include "bmLoop.h"
#include "bmSystemManager.h"
#include "bmEntityManager.h"
#include "bmPhysicsSystem.h"
#include "bmRenderSystem.h"
#include "bmScoreSystem.h"
#include "bmScoreUISystem.h"
#include "bmOxygenUISystem.h"


class bmResourceManager;
class GraphicsDevice;

class bmScene :
    public bmLoop
{
public:

    bmScene(bmStateManager* manager)
        : transitionManager(manager) { }

    virtual ~bmScene()
    {
        systemManager->onSceneSwitch();

        delete systemManager;
        delete entityManager;
    }

    void init() {


    }

    void updateEntities();
    void updateEntities(const float deltaTime);

    bmStateManager& getTransitionManager() const {
        return *transitionManager;
    }

    bmEntityManager& getEntityManager() const {
        return *entityManager;
    }

    bmSystemManager& getSystemManager() const {
        return *systemManager;
    }

    virtual void sceneEnd() { };


private:

    bmSystemManager* systemManager = new bmSystemManager();
    bmEntityManager* entityManager = new bmEntityManager();

    bmStateManager* transitionManager = nullptr;

    virtual void input() override { }
    virtual void update() override = 0;
    virtual void render(float deltaTime) override { }

    void created() override;

    virtual void sceneCreated() = 0;

};

