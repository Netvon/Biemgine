#pragma once
#include "bmLoop.h"
#include "bmSystemManager.h"
#include "bmEntityManager.h"
#include "bmRenderSystem.h"

class bmSceneManager;
class bmResourceManager;
class GraphicsDevice;

class bmScene :
	public bmLoop
{
public:
	//void addComponent(bmDrawable * newComponent);

	bmScene(bmSceneManager* manager, bmResourceManager* resourceManager)
		: sceneManager(manager), resourceManager(resourceManager) { }


	void init() {

		//auto gd = getWindow()->getGraphicsDevice();
		//bmRenderSystem renderSystem;
		////renderSystem.setGraphicsDevice(gd);

		// systemManager->addSystem(new bmRenderSystem());
	}

	void updateEntities();

	bmSceneManager& getSceneManager() const {
		return *sceneManager;
	}

	bmEntityManager& getEntityManager() const {
		return *entityManager;
	}

	bmSystemManager& getSystemManager() const {
		return *systemManager;
	}

	bmResourceManager& getResourceManager() const {
		return *resourceManager;
	}

private:

	bmSystemManager* systemManager = new bmSystemManager();
	bmEntityManager* entityManager = new bmEntityManager();

	bmSceneManager* sceneManager;
	bmResourceManager* resourceManager;

	virtual void update(float deltaTime) override = 0;
	void created() override {
		auto gd = getWindow()->getGraphicsDevice();
		auto renderSystem = new bmRenderSystem();
		renderSystem->setGraphicsDevice(gd);

		systemManager->addSystem(renderSystem);
		sceneCreated();
	}

	virtual void sceneCreated() = 0;
	virtual void sceneEnd() { };

	//virtual void drawBeforeComponents() { };
	//virtual void drawAfterComponents() { };

	//void draw() override;
	void end() {
		systemManager->onSceneSwitch();

		sceneEnd();

		systemManager->clear();
		delete systemManager;

		entityManager->clear();
		delete entityManager;
	}
};

