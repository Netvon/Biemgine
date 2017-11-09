#pragma once

#include "Biemgine.h"
#include "stdafx.h"

using std::string;
using biemgine::bmComponent;

namespace spacebiem
{
    class bmScoreComponent :
        public bmComponent
    {
    public:
        bmScoreComponent(float pScore = 0, string pName = "Score") :
            score(pScore), name(pName) {};
        ~bmScoreComponent() {};

        bmScoreComponent* setScore(const float pScore);
        float getScore() const;
        bmScoreComponent* addScore(const float pScore);

        string getName() const;

    private:
        float score;
        string name;
    };
}
