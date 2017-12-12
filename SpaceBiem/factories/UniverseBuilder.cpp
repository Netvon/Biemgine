#include "stdafx.h"
#include "UniverseBuilder.h"
#include "..\FileParser.h"
#include "..\factories\PlanetFactory.h"
#include "Biemgine.h"
#include "..\entities\PlayerEntity.h"
#include "..\entities\MummieAIEntity.h"
#include "..\entities\SnowmanAIEntity.h"

using biemgine::Entity;
using biemgine::Color;
using biemgine::PhysicsComponent;
using biemgine::PositionComponent;

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
            levelMap = fileParser.levelContent("data/savegame.csv");
        }
        else {
            levelMap = fileParser.levelContent("data/savegame.csv");
        }

        map<string, float> atmosphereM = fileParser.atmosphereContent();
        map<string, int> scoreBonus = fileParser.planetScoreContent();

        int count = 0;

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
            vector<float> physics;
            string resourceName;
            string planetScore;
            string planetName;

            for (auto& i : o.second)
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
                else if (component == "score_bonus_component") {
                    planetScore = i.second[0];

                    if (i.second[1] == "1") {
                        isDiscovered = true;
                    }
                }
                else if (component == "flag_component") {
                    flagComponent.push_back(stod(i.second[0].c_str()));
                    flagComponent.push_back(stod(i.second[1].c_str()));
                    flagComponent.push_back(stod(i.second[2].c_str()));
                }
                else if (component == "resource_component") {
                    resources.push_back(stod(i.second[0].c_str()));
                    resources.push_back(stod(i.second[1].c_str()));
                    resources.push_back(stod(i.second[2].c_str()));
                    resources.push_back(stod(i.second[3].c_str()));
                }
                else if (component == "physics_component") {
                    physics.push_back(stod(i.second[0]));
                    physics.push_back(stod(i.second[1]));
                    physics.push_back(stod(i.second[2]));
                }
                else if (component == "resource_bonus_component") {
                    resourceName = i.second[0];
                }
                else if (component == "name_component") {
                    planetName = i.second[0];
                }
            }

            if (type == "player") {
                int id = entityManager->addEntity<PlayerEntity>(stoi(xPos), stoi(yPos), Color::White(), stoi(width), stoi(height));

                if (!newGame) {
                    auto player = entityManager->getEntity(id);

                    auto oxygenComponent = player->getComponent<OxygenComponent>("oxygen");
                    oxygenComponent->setOxygenAmount(stod(oxygenAmount));
                    auto scoreComponent = player->getComponent<ScoreComponent>("score");
                    scoreComponent->setScore(stod(score));
                    auto resourceComponent = player->getComponent<ResourceComponent>("resources");
                    auto physicsComponent = player->getComponent<PhysicsComponent>("physics");
                    auto positionComponent = player->getComponent<PositionComponent>("position");

                    resourceComponent->addResource("metal", resources[0]);
                    resourceComponent->addResource("diamond", resources[1]);
                    resourceComponent->addResource("uranium", resources[2]);
                    resourceComponent->addResource("anti-matter", resources[3]);

                    physicsComponent->setVelocity({ physics[0], physics[1] }, true);
                    positionComponent->setRotation(physics[2]);
                }
            }
            else if (type == "aimummie") {
                entityManager->addEntity<MummieAIEntity>(stoi(xPos), stoi(yPos), Color::White(), stoi(width), stoi(height));
            }
            else if (type == "aisnowman") {
                entityManager->addEntity<SnowmanAIEntity>(stoi(xPos), stoi(yPos), Color::White(), stoi(width), stoi(height));
            }
            else if (type == "resource") {
                // name & score moeten nog uitgelezen worden
                resourceFactory.createPlanetResources(stod(xPos), stod(yPos), stoi(width), stoi(height), resourceName, entityManager);
            }
            else {
                if (newGame) {
                    planetFactory.create(type, stoi(xPos), stoi(yPos), stoi(width), stoi(height), entityManager, resourceFactory, nameGenerator, atmosphereM, scoreBonus);
                }
                else {
                    if (planetScore.empty())
                        planetScore = "0";

                    planetFactory.load(type, stoi(xPos), stoi(yPos), stoi(width), stoi(height), entityManager, planetName, atmosphereM, stoi(planetScore), isDiscovered, flagComponent);
                    count++;
                }  
            }
        }
    }
}
