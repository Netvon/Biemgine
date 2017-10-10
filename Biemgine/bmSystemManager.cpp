#include "stdafx.h"
#include "bmSystemManager.h"
#include "bmRenderSystem.h"


bmSystemManager::bmSystemManager()
{
	// systems.clear();
	// Push all the different systems here in the array.
	// Keep the priority of systems in mind!
	//systems.push_back(new bmRenderSystem());

}

bmSystemManager::~bmSystemManager()
{
	for (auto it = systems.begin(); it != systems.end(); ++it)
	{
		delete (*it);
	}
}

void bmSystemManager::preUpdate()
{
	for (auto* s : systems) {
		s->before();
	}
}

void bmSystemManager::postUpdate()
{
	for (auto* s : systems) {
		s->after();
	}
}

void bmSystemManager::acceptForUpdate(const bmEntity & entity)
{
	for (auto* s : systems) {
		s->update(entity);
	}
}

void bmSystemManager::addSystem(bmSystem * system)
{
	systems.push_back(system);
}

void bmSystemManager::onSceneSwitch()
{
	for (auto* s : systems) {
		s->onSceneSwitch();
	}
}
