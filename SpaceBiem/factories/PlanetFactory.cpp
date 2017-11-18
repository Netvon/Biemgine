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
        NameGenerator ng;

        FileParser fh;
        map<string, float> atmosphereM = fh.atmosphereContent();
        map<string, int> scoreBonus = fh.planetScoreContent();

        for (int x = 0; x < maxX; x++) {

            for (int y = 0; y < maxY; y++) {

                int pX = xMarge + (p_size / 2) + (x*(p_size * 2));
                int pY = yMarge + (p_size / 2) + (y*(p_size * 2));

                switch (RandomGenerator::getInstance().generate(1, 5))
                {
                case 1:
                    entities.push_back(new PlanetEarthEntity(
                        pX,
                        pY,
                        { 71, 166, 245, 255 },
                        p_size,
                        p_size,
                        scoreBonus["earth"],
                        atmosphereM["earth"],
                        ng.getName()
                    ));

                    for each (auto r in rf.getPlanetResources(pX + (p_size / 2), pY + (p_size / 2), p_size / 2, "earth"))
                    {
                        entities.push_back(r);
                    }
                    break;
                case 2:
                    entities.push_back(new PlanetSandEntity(
                        pX,
                        pY,
                        { 213,207,105,255 },
                        p_size,
                        p_size,
                        scoreBonus["sand"],
                        atmosphereM["sand"],
                        ng.getName()
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
                        scoreBonus["toxic"],
                        atmosphereM["toxic"],
                        ng.getName()
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
                        p_size,
                        scoreBonus["moon"],
                        ng.getName()
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

    void PlanetFactory::create(const string& type, int pX, int pY, int width, int height, std::shared_ptr<EntityManager> entityManager, ResourceFactory resourceFactory , NameGenerator nameGenerator, map<string, float> atmosphereM, map<string, int> scoreBonus)
    {
        if (type == "moon") {
            entityManager->addEntity<PlanetMoonEntity>(pX, pY, Color::White(), width, height, scoreBonus["moon"], nameGenerator.getName());
        }
        else if (type == "earth") {
            entityManager->addEntity<PlanetEarthEntity>(pX, pY, Color::White(), width, height, scoreBonus["earth"], atmosphereM["earth"], nameGenerator.getName());
        }
        else if (type == "sand") {
            entityManager->addEntity<PlanetSandEntity>(pX, pY, Color::White(), width, height, scoreBonus["sand"], atmosphereM["sand"], nameGenerator.getName());
        }
        else if (type == "toxic") {
            entityManager->addEntity<PlanetToxicEntity>(pX, pY, Color::White(), width, height, scoreBonus["toxic"], atmosphereM["toxic"], nameGenerator.getName());
        }
    }

    void PlanetFactory::sceneEnd(std::vector<Entity*> entities)
    {
    }
}


