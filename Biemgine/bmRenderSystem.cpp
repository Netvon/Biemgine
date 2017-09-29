#include "stdafx.h"
#include "bmRenderSystem.h"
#include "bmPositionComponent.h"
#include "bmEntity.h"



void bmRenderSystem::update(const bmEntity& entity) {

	// Get the components
	// std::map<std::string, bmComponent*> componentHM = entity->getComponentHM();
	auto pc = entity.getComponent<bmPositionComponent*>("position");

	// Check if the entity has the right components
	if (entity.hasComponent("position"))
		return;

	// Parse the base component to the right derived component
	//bmPositionComponent* pc = dynamic_cast<bmPositionComponent*>(componentHM["position"]);
	

	// Action!
	std::cout << "Rendering id:" << entity.getId() << " at x:" << pc->getX() << " and y:" << pc->getY() << std::endl;



}
