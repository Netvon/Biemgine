#pragma once

#include "Biemgine.h"
#include "stdafx.h"

using namespace std;
using namespace biemgine;

class bmScoreComponent :
    public bmComponent
{
public:
    bmScoreComponent(float pScore = 0, string pName= "Score") : score(pScore), name(pName) {};
    ~bmScoreComponent() {};

    bmScoreComponent* setScore(const float pScore)
    {
        score = pScore;
        return this;
    }

    bmScoreComponent* addScore(const float pScore)
    {
        score += pScore;
        return this;
    }

    float getScore() const
    {
        return score;
    }
    string getName() const
    {
        return name;
    }

private:
    float score;
    string name;
};
