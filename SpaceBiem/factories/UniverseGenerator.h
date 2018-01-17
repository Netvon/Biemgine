#pragma once
#include "Biemgine.h"

#include "../globals/Difficulty.h"
#include "../globals/Player.h"
#include "../FileParser.h"
#include <sstream>

using biemgine::FileHandler;
using biemgine::RandomGenerator;
using biemgine::Vector;
using biemgine::Math;

namespace spacebiem
{
    class UniverseGenerator
    {
    public:
        UniverseGenerator();

        void generate(Difficulty difficulty = Difficulty::NORMAL);

        // the system with belts
		void addPlanetarySystem(int level, int beltCount, int middleX, int middleY, int sunR, int beltMargin, int beltW, bool withWormHole);
        void addBelt(int middleX, int middleY, int minR, int maxR, float minPR, float maxPR, float minPMargin, vector<string> planetProbability);

        static Vector getRandomSpawnPosition(int pMin, int pMax, int pRadius)
        {
            auto b = RandomGenerator::getInstance().generate(0, 100);
            auto c = RandomGenerator::getInstance().generate(pMin, pMax);
        

            float a = static_cast<float>(b) / c * Math::getPI() * 2;

            return Vector{ cos(a) * pRadius, sin(a) * pRadius };
        }

    private:
        FileHandler handler;
        map<string, vector<int>> difficultySystem;
        map<string, map<string, vector<string>>> difficultyBelt;
        string currentDifficulty;

        int getNextId();
        int nextId = 1;

        void spawnPlayer(int x, int y);
        bool playerSpawned = false;
    };
}
