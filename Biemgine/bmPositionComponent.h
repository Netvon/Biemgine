#pragma once

#include "bmComponent.h"

class bmPositionComponent: public bmComponent
{
public:
	int x;
	int y;

	bmPositionComponent(int x=0, int y=0);

private:
	
};

