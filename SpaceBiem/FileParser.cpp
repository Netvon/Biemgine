#include "stdafx.h"
#include "FileParser.h"

using std::ifstream;
using std::ofstream;
using std::ios_base;

namespace spacebiem
{
    bool sortbysec(const pair<string, int> &a, const pair<string, int> &b)
    {
        return (a.second > b.second);
    }

    vector<pair<string, int>> FileParser::scoresContent()
    {
        vector<pair<string, int>> scoreMap;

        FileHandler file("highscores.csv");
        for each (auto v in file.getValues())
        {
            scoreMap.push_back(std::make_pair(v[0], stoi(v[1])));
        }
        std::sort(scoreMap.begin(), scoreMap.end(), sortbysec);

        return scoreMap;
    }

    void FileParser::writeScore(string name, int score)
    {
        FileHandler file("highscores.csv");
        file.writeLine(vector<string>({name, to_string(score)}));
    }


    map<string, float> FileParser::atmosphereContent()
    {
        map<string, float> atmosphereM;

        FileHandler file("planet_atmosphere_modifier.csv");
        for each (auto v in file.getValues())
        {
            atmosphereM[v[0]] = static_cast<float>(atof(v[1].c_str()));
        }

        return atmosphereM;
    }

    map<string, int> FileParser::planetScoreContent()
    {
        map<string, int> scoreM;

        FileHandler file("score_per_planettype.csv");
        for each (auto v in file.getValues())
        {
            scoreM[v[0]] = stoi(v[1]);
        }

        return scoreM;
    }

    map<string, int> FileParser::resourceScoreContent()
    {
        map<string, int> scoreM;

        FileHandler file("score_per_resourcetype.csv");
        for each (auto v in file.getValues())
        {
            scoreM[v[0]] = stoi(v[1]);
        }

        return scoreM;
    }
    map<string, map<string, vector<float>>> FileParser::resourceSpawnRateContent()
    {
        map<string, map<string, vector<float>>> resourceM;

        FileHandler file("resource_count_per_planettype.csv");
        for each (auto v in file.getValues())
        {
            vector<float> vector({
                static_cast<float>(atof(v[2].c_str())),
                static_cast<float>(atof(v[3].c_str())),
                static_cast<float>(atof(v[4].c_str()))
            });
            resourceM[v[0]][v[1]] = vector;
        }

        return resourceM;
    }
}
