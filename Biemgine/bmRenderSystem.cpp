#include "stdafx.h"
#include "bmRenderSystem.h"
#include "bmPositionComponent.h"
#include "bmColorComponent.h"
#include "bmEntity.h"


void bmRenderSystem::update(const bmEntity& entity) {

	// Get the components
	// std::map<std::string, bmComponent*> componentHM = entity->getComponentHM();
	auto pc = entity.getComponent<bmPositionComponent*>("position");
	auto cc = entity.getComponent<bmColorComponent*>("color");

	// Check if the entity has the right components
	if (entity.hasComponent("position"))
		return;

	// Parse the base component to the right derived component
	//bmPositionComponent* pc = dynamic_cast<bmPositionComponent*>(componentHM["position"]);
	

	// Action!
	std::cout << "Rendering id:" << entity.getId() << " at x:" << pc->getX() << " and y:" << pc->getY() << std::endl;

	float offsetX = static_cast<float>(rand() % 2) / 10.0;
	float offsetY = static_cast<float>(rand() % 2) / 10.0;

	pc->add(offsetX, offsetY);

	graphicsDevice->drawSquare(pc->getX(), pc->getY(), 50, 50, cc->getColor());
}

void bmRenderSystem::onSceneSwitch()
{
	graphicsDevice->clear();
}

void bmRenderSystem::before()
{
	graphicsDevice->clear();
}

void bmRenderSystem::after()
{
	graphicsDevice->present();
}
