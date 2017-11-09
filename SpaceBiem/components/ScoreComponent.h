#pragma once

#include "Biemgine.h"
#include "stdafx.h"

using std::string;
using biemgine::Component;

namespace spacebiem
{
    class ScoreComponent :
        public Component
    {
    public:
        ScoreComponent(float pScore = 0, string pName = "Score") :
            score(pScore), name(pName) {};
        ~ScoreComponent() {};

        ScoreComponent* setScore(const float pScore);
        float getScore() const;
        ScoreComponent* addScore(const float pScore);

        string getName() const;

    private:
        float score;
        string name;
    };
}
