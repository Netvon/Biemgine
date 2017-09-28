#include "stdafx.h"
#include "bmEntity.h"

bmEntity::bmEntity()
{
	id = rand() % 100;
}

std::map<std::string, bmComponent*> bmEntity::getComponentHM()
{

	return componentHashmap;


}

void bmEntity::clear()
{
	for (std::pair<std::string, bmComponent*> pair : componentHashmap) {
		delete pair.second;
	}

	componentHashmap.clear();
}
