#pragma once
#include "bmLoop.h"
#include "bmSystemManager.h"
#include "bmEntityManager.h"
class bmScene :
	public bmLoop
{
public:
	void addComponent(bmDrawable * newComponent);

	bmScene();

protected:
	std::vector<bmDrawable*> components;

	GLuint vao;
	GLuint vbo;

	bmSystemManager* systemManager = new bmSystemManager();
	bmEntityManager* entityManager = new bmEntityManager();

private:

	virtual void update(float deltaTime) override { }
	virtual void created() override { }

	virtual void drawBeforeComponents() { };
	virtual void drawAfterComponents() { };

	void draw() override;
	void end() override;
};

