#pragma once
#include "bmEntity.h"
class bmScoreUIEntity :
	public bmEntity
{
public:
	bmScoreUIEntity(int x = 0, int y = 50, float score = 0);
	~bmScoreUIEntity();
};

