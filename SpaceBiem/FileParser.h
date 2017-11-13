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


    private:

    };
}
