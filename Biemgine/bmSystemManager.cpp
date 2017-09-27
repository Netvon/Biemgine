#include "stdafx.h"
#include "bmSystemManager.h"
#include "bmRenderSystem.h"


bmSystemManager::bmSystemManager()
{

	// Push all the different systems here in the array.
	// Keep the priority of systems in mind!
	systems.push_back(new bmRenderSystem());


}

void bmSystemManager::updateAll(std::vector<bmEntity*> entities)
{

	for (auto* s : systems) {
		for (auto* e : entities) {

			s->update(e);
		}
	}


}
