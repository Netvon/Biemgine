#include "stdafx.h"
#include "bmEntity.h"

bmEntity::bmEntity()
{	
	id = std::rand() % 1000;
}

bmEntity::~bmEntity()
{
	for (std::pair<std::string, const bmComponent*> pair : componentHashmap) {
		delete pair.second;
	}

	componentHashmap.clear();
}
