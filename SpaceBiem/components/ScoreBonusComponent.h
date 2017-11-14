
#include "Biemgine.h"
#include "stdafx.h"

using biemgine::Component;

namespace spacebiem
{
    class ScoreBonusComponent :public Component
    {
    public:
        ScoreBonusComponent(int pScoreBonus);
        int getScoreBonus();

    private:
        int scoreBonus;
    };
}
