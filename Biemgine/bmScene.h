#pragma once
#include "bmLoop.h"
#include "bmSystemManager.h"
#include "bmEntityManager.h"

class bmSceneManager;

class bmScene :
	public bmLoop
{
public:
	void addComponent(bmDrawable * newComponent);

	bmScene(bmSceneManager* manager) : sceneManager(manager) {};

protected:
	std::vector<bmDrawable*> components;

	bmSystemManager* systemManager = new bmSystemManager();
	bmEntityManager* entityManager = new bmEntityManager();

	bmSceneManager* sceneManager;

private:

	virtual void update(float deltaTime) override { }
	virtual void created();

	virtual void drawBeforeComponents() { };
	virtual void drawAfterComponents() { };

	void draw() override;
	void end() override;
};

