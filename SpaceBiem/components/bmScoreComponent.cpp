#include "Biemgine.h"
#include "bmScoreComponent.h"

namespace spacebiem
{
    bmScoreComponent * bmScoreComponent::setScore(const float pScore)
    {
        score = pScore;
        return this;
    }

    bmScoreComponent * bmScoreComponent::addScore(const float pScore)
    {
        score += pScore;
        return this;
    }

    float bmScoreComponent::getScore() const
    {
        return score;
    }

    string bmScoreComponent::getName() const
    {
        return name;
    }
}
