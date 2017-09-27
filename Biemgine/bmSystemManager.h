#pragma once
#include "bmSystem.h"
#include "bmEntity.h"

#include <vector>

class bmSystemManager 
{
public:
	
	bmSystemManager();

	std::vector<bmSystem*> systems;

	void updateAll(std::vector<bmEntity*>);

private:

};

