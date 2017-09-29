#include "stdafx.h"
#include "bmSystemManager.h"
#include "bmRenderSystem.h"


bmSystemManager::bmSystemManager()
{

	// Push all the different systems here in the array.
	// Keep the priority of systems in mind!
	systems.push_back(new bmRenderSystem());


}

void bmSystemManager::acceptForUpdate(const bmEntity & entity)
{
	for (auto* s : systems) {
		s->update(entity);
	}
}

void bmSystemManager::clear()
{
	for (auto it = systems.begin(); it != systems.end(); ++it)
	{
		delete (*it);
	}

	systems.clear();
}
