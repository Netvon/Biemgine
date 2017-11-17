#include "ScoreBonusComponent.h"

namespace spacebiem
{
    ScoreBonusComponent::ScoreBonusComponent(int pScoreBonus) :
        scoreBonus(pScoreBonus)
    {}

    int ScoreBonusComponent::getScoreBonus() const
    {
        return scoreBonus;
    }

    void ScoreBonusComponent::setScoreGiven(bool pScoreGiven)
    {
        scoreGiven = pScoreGiven;
    }

    bool ScoreBonusComponent::isScoreGiven() const
    {
        return scoreGiven;
    }
}
