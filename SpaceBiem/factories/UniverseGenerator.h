#pragma once
#include "Biemgine.h"

#include "../globals/Difficulty.h"
#include "../globals/Player.h"
#include "../FileParser.h"

using biemgine::FileHandler;
using biemgine::RandomGenerator;

#include <sstream>


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
