#include "stdafx.h"
#include "FileHandler.h"

using std::ifstream;
using std::ofstream;
using std::ios_base;

namespace spacebiem
{
    bool sortbysec(const pair<string, int> &a, const pair<string, int> &b)
    {
        return (a.second > b.second);
    }

    vector<pair<string, int>> FileHandler::scoresContent()
    {
        vector<pair<string, int>> scoreMap;
        ifstream file("highscores.csv");
        string name;

        while (getline(file, name, ',') && name != "\n") {
            string score;
            getline(file, score);
            scoreMap.push_back(std::make_pair(name, stoi(score)));
        }
        std::sort(scoreMap.begin(), scoreMap.end(), sortbysec);

        return scoreMap;
    }

    void FileHandler::writeScore(string name, int score)
    {
        ofstream myfile;
        myfile.open("highscores.csv", ios_base::app);
        myfile << name << "," << score << ";\n";
    }
}
