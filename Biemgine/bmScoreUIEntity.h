#pragma once
#include "bmEntity.h"
class bmScoreUIEntity :
	public bmEntity
{
public:
	bmScoreUIEntity(int x = 20, int y = 30, float score = 0);
	~bmScoreUIEntity();
};

