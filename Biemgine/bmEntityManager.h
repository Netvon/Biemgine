#pragma once
#include "bmEntity.h"
#include <vector>


class bmEntityManager
{
public:


	std::vector<bmEntity*> entities;


	void AddEntity(bmEntity*);
	// Adding entities, already created? or create entities in this class, with each entity an own add function?


	// Function that fills each inputcomponent with the input data.
	void fillInput();

private:



};

