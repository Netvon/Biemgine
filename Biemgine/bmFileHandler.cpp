#include "stdafx.h"
#include "bmFileHandler.h"


bool sortbysec(const pair<string, int> &a, const pair<string, int> &b)
{
    return (a.second > b.second);
}

vector<pair<string, int>> bmFileHandler::scoresContent()
{
    vector<pair<string, int>> scoreMap;
    ifstream file("highscores.csv"); // declare file stream: http://www.cplusplus.com/reference/iostream/ifstream/
    string name;

    while (getline(file, name, ',') && name != "\n") {
        string score;
        getline(file, score);
        scoreMap.push_back(std::make_pair(name, stoi(score)));
    }
    std::sort(scoreMap.begin(), scoreMap.end(), sortbysec);

	return scoreMap;
}

void bmFileHandler::writeScore(string name, int score)
{
    ofstream myfile;
    myfile.open("highscores.csv", ios_base::app);
    myfile << name << "," << score << ";\n";
}


