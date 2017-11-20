#include "stdafx.h"
#include "UniverseBuilder.h"
#include "FileParser.h"
#include "factories\PlanetFactory.h"
#include "Biemgine.h"
#include "entities\PlayerEntity.h"

using biemgine::Entity;

namespace spacebiem
{
    UniverseBuilder::UniverseBuilder()
    {
    }

    void UniverseBuilder::build(std::shared_ptr<EntityManager> entityManager, bool newGame)
    {
        FileParser fileParser;
        PlanetFactory planetFactory;
        NameGenerator nameGenerator;
        ResourceFactory resourceFactory;

        map<string, map<string, vector<string>>> levelMap;

        if (newGame) {
            levelMap = fileParser.levelContent("data/level_1.csv");
        }
        else {
            levelMap = fileParser.levelContent("data/savegame.csv");
        }

        map<string, float> atmosphereM = fileParser.atmosphereContent();
        map<string, int> scoreBonus = fileParser.planetScoreContent();

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

                if (component == "position_component") {
                    xPos = i.second[0];
                    yPos = i.second[1];
                    width = i.second[2];
                    height = i.second[3];
                }
                else if ("oxygen_component") {
                    oxigenAmount = i.second[0];
                }
                else if ("score_component") {
                    score = i.second[0];
                }
                
            }

            if (type == "player") {
                entityManager->addEntity<PlayerEntity>(stoi(xPos), stoi(yPos), Color::White(), stoi(width), stoi(height));
            }
            else if (type == "resource") {
                // name & score moeten nog uitgelezen worden
                resourceFactory.createPlanetResources(stoi(xPos), stoi(yPos), "metal", entityManager);
            }
            else {
                if (newGame) {
                    planetFactory.create(type, stoi(xPos), stoi(yPos), stoi(width), stoi(height), entityManager, resourceFactory, nameGenerator, atmosphereM, scoreBonus);
                }
                else {
                    planetFactory.load(type, stoi(xPos), stoi(yPos), stoi(width), stoi(height), entityManager, "name", atmosphereM, scoreBonus);
                }  
            }
        }
    }
}
