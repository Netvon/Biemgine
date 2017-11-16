#include "Biemgine.h"
#include "PlanetFactory.h"

namespace spacebiem
{
    vector<Entity*> PlanetFactory::sceneStart(int windowW, int windowH)
    {
        vector<Entity*> entities;


        int maxX = 3;
        int maxY = 2;

        int xMarge;
        float p_size;
        int yMarge;

        if (windowW / maxX < windowH / maxY) {
            xMarge = 60;
            p_size = (windowW - (xMarge*2)) / (maxX*2);
            yMarge = ((windowH - (p_size * 2 * maxY)) / 2);
        }
        else {
            yMarge = 60;
            p_size = ((windowH - (yMarge*2)) / (maxY*2));
            xMarge = ((windowW - (p_size * 2 * maxX)) / 2);
        }


        ResourceFactory rf;

        FileParser fh;
        map<string, float> atmosphereM = fh.atmosphereContent();
        map<string, int> scoreBonus = fh.planetScoreContent();

        for (int x = 0; x < maxX; x++) {

            for (int y = 0; y < maxY; y++) {

                int pX = xMarge + (p_size / 2) + (x*(p_size * 2));
                int pY = yMarge + (p_size / 2) + (y*(p_size * 2));

                PlanetEntity * planet = nullptr;

                switch (RandomGenerator::getInstance().generate(1, 5))
                {
                case 1:
                    planet = new PlanetEarthEntity(
                        pX,
                        pY,
                        { 255, 255, 255, 255 },
                        p_size,
                        p_size,
                        atmosphereM["earth"]
                    );

                    planet->createScoreBonus(scoreBonus["earth"]);

                    entities.push_back(planet);
                    for each (auto r in rf.getPlanetResources(pX + (p_size / 2), pY + (p_size / 2), p_size / 2, "earth"))
                    {
                        entities.push_back(r);
                    }
                    break;
                case 2:
                    entities.push_back(new PlanetSandEntity(
                        pX,
                        pY,
                        { 255, 255, 255, 255 },
                        p_size,
                        p_size,
                        atmosphereM["sand"]
                    ));
                    for each (auto r in rf.getPlanetResources(pX + (p_size / 2), pY + (p_size / 2), p_size / 2, "sand"))
                    {
                        entities.push_back(r);
                    }
                    break;
                case 3:
                    entities.push_back(new PlanetToxicEntity(
                        pX,
                        pY,
                        { 127, 0, 255, 255 },
                        p_size,
                        p_size,
                        atmosphereM["toxic"]
                    ));
                    for each (auto r in rf.getPlanetResources(pX+(p_size/2), pY+(p_size/2), p_size/2, "toxic"))
                    {
                        entities.push_back(r);
                    }
                    break;
                case 4:
                    entities.push_back(new PlanetMoonEntity(
                        pX,
                        pY,
                        { 255, 255, 255, 255 },
                        p_size,
                        p_size
                    ));
                    for each (auto r in rf.getPlanetResources(pX + (p_size / 2), pY + (p_size / 2), p_size / 2, "moon"))
                    {
                        entities.push_back(r);
                    }
                    break;
                default:
                    break;
                }
            }

        }

        return entities;
    }

    Entity * PlanetFactory::create(const string& type, int pX, int pY, int width, int height)
    {
        if (type == "moon") {

        }


        new PlanetMoonEntity(
            pX,
            pY,
            { 255, 255, 255, 255 },
            width,
            height
        );

        return nullptr;
    }

    void PlanetFactory::sceneEnd(std::vector<Entity*> entities)
    {
    }
}


