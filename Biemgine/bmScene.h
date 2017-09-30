#pragma once
#include "bmLoop.h"
#include "bmSystemManager.h"
#include "bmEntityManager.h"

class bmSceneManager;
class bmResourceManager;

class bmScene :
	public bmLoop
{
public:
	//void addComponent(bmDrawable * newComponent);

	bmScene(bmSceneManager* manager, bmResourceManager* resourceManager)
		: sceneManager(manager), resourceManager(resourceManager) {};

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

	virtual void update(float deltaTime) override { }
	virtual void created();

	//virtual void drawBeforeComponents() { };
	//virtual void drawAfterComponents() { };

	//void draw() override;
	void end() override;
};

