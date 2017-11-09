#pragma once
#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using std::string;
using std::vector;
using std::pair;

namespace spacebiem
{
    class FileHandler
    {
    public:
        vector<pair<string, int>> scoresContent();
        void writeScore(string name, int score);
    };
}
