#include "stdafx.h"
#include "bmScene.h"

void bmScene::addComponent(bmDrawable * newComponent)
{
	components.push_back(newComponent);
	newComponent->init();
}

bmScene::bmScene()
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo);
}

void bmScene::draw()
{
	drawBeforeComponents();

	for (auto* c : components) {
		c->draw();
	}

	drawAfterComponents();
}

void bmScene::end()
{
	for (auto* c : components) {
		delete c;
	}
}