#pragma once

#include "bmComponent.h"

#include <map>
#include <iostream>
#include <cassert>

class bmEntity
{
public:
	bmEntity();
	std::map<std::string, bmComponent*> getComponentHM();
	int id;

protected:

	std::map<std::string, bmComponent*> componentHashmap;


};

