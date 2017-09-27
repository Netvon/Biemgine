#include "stdafx.h"
#include "bmRenderSystem.h"
#include "bmPositionComponent.h"
#include "bmEntity.h"



void bmRenderSystem::update(bmEntity* entity) {

	// Get the components
	std::map<std::string, bmComponent*> componentHM = entity->getComponentHM();

	// Check if the entity has the right components
	if (componentHM.find("position") == componentHM.end()) return;

	// Parse the base component to the right derived component
	bmPositionComponent* pc = dynamic_cast<bmPositionComponent*>(componentHM["position"]);
	

	// Action!
	std::cout << "Rendering id:" << entity->id << " at x:" << pc->x << " and y:" << pc->y << std::endl;



}
