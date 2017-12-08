#pragma once

#include "Biemgine.h"

#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using std::string;
using std::vector;
using std::pair;

using biemgine::FileHandler;


namespace spacebiem
{
    class FileParser
    {
    public:
        vector<pair<string, int>> scoresContent();
        void writeScore(string name, int score);
        map<string, float> atmosphereContent();
        map<string, int> planetScoreContent();
        map<string, int> resourceScoreContent();
        map<string, map<string, vector<float>>> resourceSpawnRateContent();
        map<string, int> resourcesContent();
        void writeNewResources(map<string, int> resources); 

        map<string, map<string, vector<string>>> levelContent(string fileName);

        map<string, vector<int>> DifficultySystemContent();
        map<string, map<string, vector<string>>> DifficultyBeltContent();


    private:

    };
}
