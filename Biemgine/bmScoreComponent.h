#pragma once
#include "bmComponent.h"

class bmScoreComponent :
    public bmComponent
{
public:
    bmScoreComponent(float pScore = 0) : score(pScore) {};
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

private:
    float score;
};
