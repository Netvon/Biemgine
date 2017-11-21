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

        for (auto& o : levelMap)
        {
            string id = o.first.c_str();
            string type = id.substr(id.find('_') + 1, id.size());

            string xPos;
            string yPos;
            string width;
            string height;
            string oxygenAmount;
            string score;
            bool isDiscovered = false;
            vector<float> flagComponent;
            vector<int> resources;

            for (auto& i : o.second)
            for(auto& i : o.second)
            {
                string component = i.first.c_str();

                if (component == "position_component") {
                    xPos = i.second[0];
                    yPos = i.second[1];
                    width = i.second[2];
                    height = i.second[3];
                }
                else if (component == "oxygen_component") {
                    oxygenAmount = i.second[0];
                }
                else if (component == "score_component") {
                    score = i.second[0];
                }
                else if (component == "collidable_component") {
                    if (i.second[0] == "1") {
                        isDiscovered = true;
                    }
                }
                else if (component == "flag_component") {
                    flagComponent[0] = static_cast<float>(atof(i.second[0].c_str()));
                    flagComponent[1] = static_cast<float>(atof(i.second[1].c_str()));
                    flagComponent[2] = static_cast<float>(atof(i.second[2].c_str()));
                }
                else if (component == "resource_component") {
                    resources[0] = atoi(i.second[0].c_str());
                    resources[1] = atoi(i.second[1].c_str());
                    resources[2] = atoi(i.second[2].c_str());
                    resources[3] = atoi(i.second[3].c_str());
                }
            }

            if (type == "player") {
                int id = entityManager->addEntity<PlayerEntity>(stoi(xPos), stoi(yPos), Color::White(), stoi(width), stoi(height));

                if (!newGame) {
                    auto player = entityManager->getEntity(id);

                    auto oxygenComponent = player->getComponent<OxygenComponent*>("oxygen");
                    oxygenComponent->setOxygenAmount(stod(oxygenAmount));
                    auto scoreComponent = player->getComponent<ScoreComponent*>("score");
                    scoreComponent->setScore(stod(score));
                    auto resourceComponent = player->getComponent<ResourceComponent*>("resources");

                    resourceComponent->addResource("metal", resources[0]);
                    resourceComponent->addResource("diamond", resources[1]);
                    resourceComponent->addResource("uranium", resources[2]);
                    resourceComponent->addResource("anti-matter", resources[3]);
                }
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
                    planetFactory.load(type, stoi(xPos), stoi(yPos), stoi(width), stoi(height), entityManager, "name", atmosphereM, scoreBonus, isDiscovered, flagComponent);
                }  
            }
        }
    }
}
