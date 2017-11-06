#pragma once
#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

class bmFileHandler
{
public:

    vector<pair<string,int>> scoresContent();
    void writeScore(string name, int score);

protected:

};

