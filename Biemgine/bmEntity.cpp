#include "stdafx.h"
#include "bmEntity.h"

#include <random>

bmEntity::bmEntity()
{
	std::mt19937 rng;
	rng.seed(std::random_device()());
	std::uniform_int_distribution<std::mt19937::result_type> dist6(1, INT_MAX);

	id = dist6(rng);//std::rand() % 1000;
}

bmEntity::~bmEntity()
{
	for (std::pair<std::string, const bmComponent*> pair : componentHashmap) {
		delete pair.second;
	}

	componentHashmap.clear();
}
