#include "stdafx.h"
#include "bmEntity.h"

bmEntity::bmEntity()
{	
	id = std::rand() % 100;
}


void bmEntity::clear()
{
	for (std::pair<std::string, const bmComponent*> pair : componentHashmap) {
		delete pair.second;
	}

	componentHashmap.clear();
}
