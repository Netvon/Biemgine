#pragma once

#include "bmComponent.h"
#include "bmEntity.h"

#include <map>
#include <iostream>
#include <cassert>

class bmSystem
{
public:
	virtual void update(bmEntity*) { };

private:


};

