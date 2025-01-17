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

        FileHandler file("data/highscores.csv");
        for each (auto v in file.getValues())
        {
            scoreMap.push_back(std::make_pair(v[0], stoi(v[1])));
        }
        std::sort(scoreMap.begin(), scoreMap.end(), sortbysec);

        return scoreMap;
    }

    void FileParser::writeScore(string name, int score)
    {
        FileHandler file("data/highscores.csv");
        file.writeLine(vector<string>({name, to_string(score)}));
    }


    map<string, float> FileParser::atmosphereContent()
    {
        map<string, float> atmosphereM;

        FileHandler file("data/planet_atmosphere_modifier.csv");
        for each (auto v in file.getValues())
        {
            atmosphereM[v[0]] = static_cast<float>(atof(v[1].c_str()));
        }

        return atmosphereM;
    }

    map<string, int> FileParser::planetScoreContent()
    {
        map<string, int> scoreM;

        FileHandler file("data/score_per_planettype.csv");
        for each (auto v in file.getValues())
        {
            scoreM[v[0]] = stoi(v[1]);
        }

        return scoreM;
    }

    map<string, int> FileParser::resourceScoreContent()
    {
        map<string, int> scoreM;

        FileHandler file("data/score_per_resourcetype.csv");
        for each (auto v in file.getValues())
        {
            scoreM[v[0]] = stoi(v[1]);
        }

        return scoreM;
    }

    map<string, map<string, vector<float>>> FileParser::resourceSpawnRateContent()
    {
        map<string, map<string, vector<float>>> resourceM;

        FileHandler file("data/resource_count_per_planettype.csv");
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

    map<string, int> FileParser::resourcesContent()
    {
        return resourcesContent(Player::current());
    }

    map<string, int> FileParser::resourcesContent(const Player& forPlayer)
    {
        map<string, int> resourceM;

        FileHandler file(forPlayer.resourceLocation());
        for each (auto v in file.getValues())
        {
            resourceM[v[0]] = stoi(v[1]);
        }

        return resourceM;
    }

    void FileParser::writeNewResources(map<string, int> resources)
    {
        map<string, int> content = resourcesContent();
        for (auto r : resources) {
            content[r.first] += r.second;
        }

        FileHandler file(Player::current().resourceLocation(), true);
        for (auto r : content) {
            file.writeLine(vector<string>({ r.first, to_string(r.second) }));
        }

    }

    map<string, map<string, vector<string>>> FileParser::levelContent(string fileName) {
        map<string, map<string, vector<string>>> levelMap;
        map<string, vector<string>> innerMap;

        string currentKey;
        string previousKey;

        FileHandler file(fileName);

        int i = 0;
        
        for (auto& v : file.getValues())
        {
            if (i == 0) {
                i++;
                continue;
            }

             currentKey = v[0];

             vector<string> vector;

             for (size_t j = 2; j < v.size(); j++)
             {
                 vector.push_back(v[j]);
             }

             if (currentKey != previousKey) {
                 innerMap.clear();
             }

            innerMap[v[1]] = vector;
            levelMap[v[0]] = innerMap;

            previousKey = currentKey;

            i++;
        }

        return levelMap;
    }

    map<string, vector<int>> FileParser::DifficultySystemContent()
    {
        map<string, vector<int>> systemM;

        FileHandler file("data/difficulty_system.csv");
        for each (auto v in file.getValues())
        {
            vector<int> vector({
                stoi(v[1]),
                stoi(v[2]),
                stoi(v[3]),
                stoi(v[4]),
                stoi(v[5]),
                stoi(v[6]),
            });
            systemM[v[0]] = vector;
        }

        return systemM;
    }

    map<string, map<string, vector<string>>> FileParser::DifficultyBeltContent()
    {
        map<string, map<string, vector<string>>> beltM;

        FileHandler file("data/difficulty_belts.csv");
        for each (auto v in file.getValues())
        {
            vector<string> vector({
                v[2],
                v[3],
                v[4],
                v[5],
            });
            beltM[v[0]][v[1]] = vector;
        }

        return beltM;
    }

    map<Difficulty, bool> FileParser::progressContent()
    {
        map<Difficulty, bool> progress;

        FileHandler file(Player::current().progressLocation());
        for (auto v : file.getValues())
        {
            if (v[1] == "1") {
                progress[(Difficulty)stoi(v[0])] = true;
            }
            else {
                progress[(Difficulty)stoi(v[0])] = false;
            }
        }

        return progress;
    }


    void FileParser::writeProgress(map<Difficulty, bool> resources)
    {
        map<Difficulty, bool> content = progressContent();
        for (auto r : resources) {
            content[r.first] += r.second;
        }

        FileHandler file(Player::current().progressLocation(), true);
        for (auto r : content) {
            file.writeLine(vector<string>({ to_string(static_cast<unsigned int>(r.first)), to_string(r.second) }));
        }

    }

}
