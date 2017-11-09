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
        myfile << name << "," << score << "\n";
    }


    map<string, float> FileHandler::atmosphereContent()
    {
        map<string, float> atmosphereM;
        ifstream file("planet_atmosphere_modifier.csv");
        string planet;

        while (getline(file, planet, ',') && planet != "\n") {
            string modifier;
            getline(file, modifier);
            atmosphereM[planet] = atof(modifier.c_str());
        }

        return atmosphereM;
    }

    map<string, int> FileHandler::planetScoreContent()
    {
        map<string, int> scoreM;
        ifstream file("score_per_planettype.csv");
        string planet;

        while (getline(file, planet, ',') && planet != "\n") {
            string score;
            getline(file, score);
            scoreM[planet] = stoi(score);
        }

        return scoreM;
    }

    map<string, int> FileHandler::resourceScoreContent()
    {
        map<string, int> scoreM;
        ifstream file("score_per_resourcetype.csv");
        string resource;

        while (getline(file, resource, ',') && resource != "\n") {
            string score;
            getline(file, score);
            scoreM[resource] = stoi(score);
        }

        return scoreM;
    }
}
