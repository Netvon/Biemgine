#include "ScoreBonusComponent.h"

namespace spacebiem
{
    ScoreBonusComponent::ScoreBonusComponent(int pScoreBonus, bool pScoreGiven) :
        scoreBonus(pScoreBonus),
        scoreGiven(pScoreGiven)
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
