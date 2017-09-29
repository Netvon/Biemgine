#pragma once
#include "bmSystem.h"
#include "bmEntity.h"

#include <vector>

class bmSystemManager 
{
public:
	
	bmSystemManager();
	void acceptForUpdate(const bmEntity& entity);

	void clear();
private:
	std::vector<bmSystem*> systems;

};

