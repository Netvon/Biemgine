#include "Biemgine.h"
#include "ScoreComponent.h"

namespace spacebiem
{
    ScoreComponent * ScoreComponent::setScore(const float pScore)
    {
        score = pScore;
        return this;
    }

    ScoreComponent * ScoreComponent::addScore(const float pScore)
    {
        score += pScore;
        return this;
    }

    float ScoreComponent::getScore() const
    {
        return score;
    }

    string ScoreComponent::getName() const
    {
        return name;
    }
}
