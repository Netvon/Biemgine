#pragma once
#include "bmEntity.h"
#include "bmSystemManager.h"
#include <vector>


class bmEntityManager
{
public:

	~bmEntityManager();
	int addEntity(bmEntity* entity);
	// Adding entities, already created? or create entities in this class, with each entity an own add function?

	// Function that fills each inputcomponent with the input data.
	void fillInput();

    void updateEntities(bmSystemManager * manager);
    void updateEntities(bmSystemManager * manager, const float deltaTime);

private:

	std::vector<bmEntity*> entities;

};

