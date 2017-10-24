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
    //void addComponent(bmDrawable * newComponent);

    bmScene(bmStateManager* manager/*, bmResourceManager* resourceManager*/)
        : transitionManager(manager)/*, resourceManager(resourceManager)*/ { }

    virtual ~bmScene()
    {
        systemManager->onSceneSwitch();


        //systemManager->clear();
        delete systemManager;

        //entityManager->clear();
        delete entityManager;
    }

    void init() {

        //auto gd = getWindow()->getGraphicsDevice();
        //bmRenderSystem renderSystem;
        ////renderSystem.setGraphicsDevice(gd);

        // systemManager->addSystem(new bmRenderSystem());
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

    /*bmResourceManager& getResourceManager() const {
        return *resourceManager;
    }*/

    virtual void sceneEnd() { };


private:

    bmSystemManager* systemManager = new bmSystemManager();
    bmEntityManager* entityManager = new bmEntityManager();

    bmStateManager* transitionManager = nullptr;
    //bmResourceManager* resourceManager;

    virtual void input() override { }
    virtual void update() override = 0;
    virtual void render(float deltaTime) override { }

    void created() override;

    virtual void sceneCreated() = 0;

    //virtual void drawBeforeComponents() { };
    //virtual void drawAfterComponents() { };

    //void draw() override;
    void end() {
        
    }
};

