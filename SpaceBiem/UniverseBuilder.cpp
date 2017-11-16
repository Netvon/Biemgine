#include "stdafx.h"
#include "UniverseBuilder.h"
#include "FileParser.h"
#include "factories/PlanetFactory.h"
#include "Biemgine.h"

using biemgine::Entity;

namespace spacebiem
{
    UniverseBuilder::UniverseBuilder()
    {
    }

    void UniverseBuilder::build(int windowW, int windowH, vector<Entity*>& placeIn)
    {
        FileParser fileParser;
        PlanetFactory planetFactory;

        map<string, map<string, vector<string>>> levelMap = fileParser.levelContent();

        for each (auto o in levelMap)
        {
            string id = o.first.c_str();
            string type = id.substr(id.find('_') + 1, id.size());

            string xPos;
            string yPos;
            string width;
            string height;
            string oxigenAmount;
            string score;

            for each (auto i in o.second)
            {
                string component = i.first.c_str();

                for each (auto v in i.second)
                {
                    if (component == "position_component") {
                        xPos = v[0];
                        yPos = v[1];
                        width = v[2];
                        height = v[3];
                    }
                    else if ("oxygen_component") {
                        oxigenAmount = v[0];
                    }
                    else if ("score_component") {
                        score = v[0];
                    }
                }

                placeIn.push_back(planetFactory.create(type, stoi(xPos), stoi(yPos), stoi(width), stoi(height)));
            }

        }
    }
}
