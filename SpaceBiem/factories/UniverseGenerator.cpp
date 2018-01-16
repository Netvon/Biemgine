#include "stdafx.h"
#include "UniverseGenerator.h"

namespace spacebiem
{
    UniverseGenerator::UniverseGenerator()
    {
        FileParser parser;
        difficultySystem = parser.DifficultySystemContent();
        difficultyBelt = parser.DifficultyBeltContent();
    }

    void UniverseGenerator::generate(Difficulty difficulty)
    {
        if (difficulty == Difficulty::NORMAL) currentDifficulty = "normal";
        else if (difficulty == Difficulty::CHALLENING) currentDifficulty = "challenging";
        else if (difficulty == Difficulty::EXPERT) currentDifficulty = "expert";

        // If there didn't spawn any earth planet for the player, try again.
        while (!playerSpawned) {

            
            handler = FileHandler{ Player::current().saveLocation(), true };

            handler.writeLine("entity_id_type,component_type,value_1,value_2,value_3,value_4");

            int beltMargin = difficultySystem[currentDifficulty][0];
            int beltW = difficultySystem[currentDifficulty][1];
            int minBelt = difficultySystem[currentDifficulty][2];
            int maxBelt = difficultySystem[currentDifficulty][3];
            int sunR = difficultySystem[currentDifficulty][4];
            int interstellarMargin = difficultySystem[currentDifficulty][5];

            int beltCount = RandomGenerator::getInstance().generate(minBelt, maxBelt);

            int systemR = (sunR)+beltMargin + ((beltCount - 1) * (beltW + beltMargin)) + beltW + interstellarMargin;

            int middleX = 0;
            int middleY = 0;

            // level 0 system (middle)
            addPlanetarySystem(0, beltCount, middleX, middleY, sunR, beltMargin, beltW, false);


            // level 1 systems (neighbouring middle)
            int angleMinIncr = 25;
            int angleMaxIncr = 35;
            float startAngle = static_cast<float>(RandomGenerator::getInstance().generate(1, 100));
            float newAngle = startAngle;

            int count = 3;
            int systemWithWormHole = RandomGenerator::getInstance().generate(1, count);

            while (count > 0) {

                float angle = newAngle / 100 * 3.1415926535897f * 2;

                float r = systemR * 2;
                int pX = middleX + static_cast<int>(cos(angle)*r);
                int pY = middleY + static_cast<int>(sin(angle)*r);

                addPlanetarySystem(0, beltCount, pX, pY, ((count != systemWithWormHole)? sunR : 450), beltMargin, beltW, (count == systemWithWormHole));

                newAngle += RandomGenerator::getInstance().generate(angleMinIncr, angleMaxIncr);
                count--;
            }


            handler.close();
        }

    }

    void UniverseGenerator::addPlanetarySystem(int level, int beltCount, int middleX, int middleY, int sunR, int beltMargin, int beltW, bool withWormHole)
    {

        int sunId = getNextId();
        string sunType = ((withWormHole)?"wormhole":"lava");

        handler.writeLine(
            to_string(sunId)+"_"+sunType + "," +
            "position_component," +
            to_string(middleX - (sunR / 2)) + "," +
            to_string(middleY - (sunR / 2)) + "," +
            to_string(sunR) + "," +
            to_string(sunR)
        );


        while (beltCount > 0) {
            beltCount--;

            int minR = (sunR)+beltMargin + (beltCount * (beltW + beltMargin));
            int maxR = minR + beltW;
            string beltType;

            if (beltCount >= 3) {
                beltType = "asteroid";
            }
            else if (beltCount == 2) {
                beltType = "outer";
            }
            else if (beltCount == 1) {
                beltType = "middle";
            }
            else if (beltCount == 0) {
                beltType = "inner";
            }

            float minPR = static_cast<float>(atof(difficultyBelt[currentDifficulty][beltType][0].c_str()));
            float maxPR = static_cast<float>(atof(difficultyBelt[currentDifficulty][beltType][1].c_str()));
            float minPMargin = static_cast<float>(atof(difficultyBelt[currentDifficulty][beltType][2].c_str()));

            string input = difficultyBelt[currentDifficulty][beltType][3];
            istringstream ss(input);
            string token;
            vector<string> planetProbability;

            while (getline(ss, token, '/')) {
                planetProbability.push_back(token);
            }

            addBelt(middleX, middleY, minR, maxR, minPR, maxPR, minPMargin, planetProbability);

        }
    }


    void UniverseGenerator::addBelt(int middleX, int middleY, int minR, int maxR, float minPR, float maxPR, float minPMargin, vector<string> planetProbability)
    {

        float planetsInAngle = ((minR + maxR) / 2) * 3.1415926535897f * 2 / ((maxPR * 2) + minPMargin);

        float angleMinIncr = (1 / planetsInAngle) * 100;
        float angleMaxIncr = angleMinIncr * 1.3f;
        float startAngle = static_cast<float>(RandomGenerator::getInstance().generate(1, 100));
        float newAngle = startAngle;

        while (startAngle + (100 - angleMinIncr) > newAngle) {

            float angle = newAngle / 100 * 3.1415926535897f * 2;

            int pRadius = RandomGenerator::getInstance().generate(minPR, maxPR);
            int pId = getNextId();
            string pType = planetProbability[RandomGenerator::getInstance().generate(0, planetProbability.size())];

            int minimumR = minR + pRadius;
            int maximumR = maxR - pRadius;

            float r = RandomGenerator::getInstance().generate(minimumR, maximumR);
            int pX = middleX + static_cast<int>(cos(angle)*r);
            int pY = middleY + static_cast<int>(sin(angle)*r);

            if (pType == "earth") spawnPlayer(pX, pY - pRadius + 50);

            handler.writeLine(
                to_string(pId) + "_" + pType + "," +
                "position_component," +
                to_string(pX - (pRadius / 2)) + "," +
                to_string(pY - (pRadius / 2)) + "," +
                to_string(pRadius) + "," +
                to_string(pRadius)
            );

            float a = RandomGenerator::getInstance().generate(0.f, 1.f);
            a = a * Math::getPI() * 2;

            auto radius = pRadius - 50;

            auto x = radius * cos(a);
            auto y = radius * sin(a);
            
            if (pType == "sand") {
                pId = getNextId();

                handler.writeLine(
                    to_string(pId) + "_aimummie," +
                    "position_component," +
                    to_string(pX + x) + "," +
                    to_string(pY + y) + "," +
                    "50,50"
                );
            }
            else if (pType == "ice") {
                handler.writeLine(
                    to_string(pId) + "_aisnowman," +
                    "position_component," +
                    to_string(pX + x) + "," +
                    to_string(pY + y) + "," +
                    "50,50"
                );
            }

            newAngle += static_cast<float>(RandomGenerator::getInstance().generate(angleMinIncr, angleMaxIncr));
        }

    }

    int UniverseGenerator::getNextId() {
        nextId++;
        return nextId;
    }

    void UniverseGenerator::spawnPlayer(int x, int y) {

        if (playerSpawned) return;

        handler.writeLine("2_player,position_component,"+ to_string(x) +","+ to_string(y) +",25,50");
        handler.writeLine("2_player,score_component,0");
        handler.writeLine("2_player,oxygen_component,500");

        playerSpawned = true;
    }
}
