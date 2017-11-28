#include "stdafx.h"
#include "UniverseGenerator.h"

namespace spacebiem
{
    UniverseGenerator::UniverseGenerator()
    {
    }

    void UniverseGenerator::generate(Difficulty difficulty)
    {
        handler = new FileHandler{ "data/level_normal.csv", true };

        handler->writeLine("entity_id_type,component_type,value_1,value_2,value_3,value_4");

        handler->writeLine("2_player,position_component,600,300,25,50");
        handler->writeLine("2_player,score_component,100");
        handler->writeLine("2_player,oxygen_component,500");

        addPlanetarySystem(0, 2, 1000, 900);

        delete handler;
    }

    void UniverseGenerator::addPlanetarySystem(int level, int beltCount, int middleX, int middleY)
    {

        int sunId = RandomGenerator::getInstance().generate(1, 100000);
        string sunType = "moon";
        int sunR = 500;
        int sunX = middleX;
        int sunY = middleY;
        

        handler->writeLine(
            to_string(sunId)+"_"+sunType + "," +
            "position_component," +
            to_string(sunX - (sunR / 2)) + "," +
            to_string(sunY - (sunR / 2)) + "," +
            to_string(sunR) + "," +
            to_string(sunR)
        );


        int beltMargin = 40;

        int beltW = 600;



        while (beltCount > 0) {
            beltCount--;

            int minR = (sunR)+beltMargin + (beltCount * (beltW + beltMargin));
            int maxR = minR + beltW;

            if (beltCount >= 2) {
                addAsteroidBelt(middleX, middleY, minR, maxR);
            }
            else if (beltCount == 1) {
                addOuterBelt(middleX, middleY, minR, maxR);
            }
            else if (beltCount == 0) {
                addInnerBelt(middleX, middleY, minR, maxR);
            }

        }


    }

    void UniverseGenerator::addStarSystem(int level, int beltCount, int middleX, int middleY)
    {
    }

    void UniverseGenerator::addInnerBelt(int middleX, int middleY, int minR, int maxR)
    {

        float minPR = 250;
        float maxPR = 300;
        float minPMargin = 200;

        vector<string> planetProbability{"sand", "moon"};

        addBelt(middleX, middleY, minR, maxR, minPR, maxPR, minPMargin, planetProbability);

    }

    void UniverseGenerator::addOuterBelt(int middleX, int middleY, int minR, int maxR)
    {
        float minPR = 250;
        float maxPR = 300;
        float minPMargin = 200;

        vector<string> planetProbability{ "earth", "toxic" };

        addBelt(middleX, middleY, minR, maxR, minPR, maxPR, minPMargin, planetProbability);
    }

    void UniverseGenerator::addAsteroidBelt(int middleX, int middleY, int minR, int maxR)
    {
        float minPR = 100;
        float maxPR = 150;
        float minPMargin = 50;

        vector<string> planetProbability{ "moon" };

        addBelt(middleX, middleY, minR, maxR, minPR, maxPR, minPMargin, planetProbability);
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
            int pId = RandomGenerator::getInstance().generate(1, 100000);
            string pType = planetProbability[RandomGenerator::getInstance().generate(0, planetProbability.size()-1)];

            int minimumR = minR + pRadius;
            int maximumR = maxR - pRadius;

            float r = RandomGenerator::getInstance().generate(minimumR, maximumR);
            int pX = middleX + static_cast<int>(cos(angle)*r);
            int pY = middleY + static_cast<int>(sin(angle)*r);


            handler->writeLine(
                to_string(pId) + "_" + pType + "," +
                "position_component," +
                to_string(pX - (pRadius / 2)) + "," +
                to_string(pY - (pRadius / 2)) + "," +
                to_string(pRadius) + "," +
                to_string(pRadius)
            );


            newAngle += static_cast<float>(RandomGenerator::getInstance().generate(angleMinIncr, angleMaxIncr));
        }

    }


}
