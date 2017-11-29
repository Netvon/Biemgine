#pragma once
#include "Biemgine.h"

#include "../globals/Difficulty.h"

using biemgine::FileHandler;
using biemgine::RandomGenerator;


namespace spacebiem
{

    class UniverseGenerator
    {
    public:
        UniverseGenerator();

        void generate(Difficulty difficulty = Difficulty::NORMAL);


        // Easier system with 1 star
        void addPlanetarySystem(int level, int beltCount, int middleX, int middleY);

        // Harder system with more than 1 star
        void addStarSystem(int level, int beltCount, int middleX, int middleY);

        
        // hot planets
        void addInnerBelt(int middleX, int middleY, int minR, int maxR);

        // Livable planets
        void addMiddleBelt(int middleX, int middleY, int minR, int maxR);

        // cold planets
        void addOuterBelt(int middleX, int middleY, int minR, int maxR);

        // Tiny moons (not always there)
        void addAsteroidBelt(int middleX, int middleY, int minR, int maxR);


        void addBelt(int middleX, int middleY, int minR, int maxR, float minPR, float maxPR, float minPMargin, vector<string> planetProbability);


    private:
        FileHandler* handler;
            

    };
}
