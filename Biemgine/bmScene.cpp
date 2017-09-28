#include "stdafx.h"
#include "bmScene.h"

void bmScene::addComponent(bmDrawable * newComponent)
{
	components.push_back(newComponent);
	newComponent->init();
}

void bmScene::created()
{
	
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
		c->clear();
		delete c;
	}

	systemManager->clear();
	delete systemManager;

	entityManager->clear();
	delete entityManager;
}