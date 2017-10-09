#include "stdafx.h"
#include "bmEntity.h"

bmEntity::bmEntity()
{	
	id = std::rand() % 1000;
}


void bmEntity::clear()
{
	for (std::pair<std::string, const bmComponent*> pair : componentHashmap) {
		delete pair.second;
	}

	componentHashmap.clear();
}
