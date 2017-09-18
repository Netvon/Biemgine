#pragma once
#include "bmLoop.h"
class bmScene :
	public bmLoop
{
public:
	void addComponent(bmComponent * newComponent);

	bmScene();

private:
	std::vector<bmComponent*> components;

	GLuint vao;
	GLuint vbo;
private:

	virtual void update() override { }
	virtual void created() override { }

	virtual void drawBeforeComponents() { };
	virtual void drawAfterComponents() { };

	void draw() override;
	void end() override;
};

