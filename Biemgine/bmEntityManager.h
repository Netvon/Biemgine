#pragma once
#include "bmEntity.h"
#include "bmSystemManager.h"
#include <vector>


class bmEntityManager
{
public:

	int addEntity(bmEntity* entity);
	// Adding entities, already created? or create entities in this class, with each entity an own add function?

	// Function that fills each inputcomponent with the input data.
	void fillInput();

	void clear();

	void updateEntities(bmSystemManager * manager);	

private:

	std::vector<bmEntity*> entities;

};

