#include "ScoreBonusComponent.h"

namespace spacebiem
{
    ScoreBonusComponent::ScoreBonusComponent(int pScoreBonus) :
        scoreBonus(pScoreBonus)
    {}

    int ScoreBonusComponent::getScoreBonus()
    {
        return scoreBonus;
    }
}
