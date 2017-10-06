#pragma once
#include "bmSystem.h"
#include "bmEntity.h"

#include <vector>

class bmSystemManager 
{
public:
	
	bmSystemManager();
	void preUpdate();
	void postUpdate();
	void acceptForUpdate(const bmEntity& entity);

	void addSystem(bmSystem* system);

	void onSceneSwitch();
	void clear();
private:
	std::vector<bmSystem*> systems;

};

