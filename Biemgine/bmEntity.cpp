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
