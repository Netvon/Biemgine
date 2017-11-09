#include "Biemgine.h"
#include "PlanetFactory.h"

namespace spacebiem
{
    vector<Entity*> PlanetFactory::sceneStart(int windowW, int windowH)
    {
        vector<Entity*> entities;


        int maxX = 6;
        int maxY = 3;

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


        FileHandler fh;
        map<string, float> atmosphereM = fh.atmosphereContent();
        
        for (int x = 0; x < maxX; x++) {

            for (int y = 0; y < maxY; y++) {


                switch (RandomGenerator::getInstance().generate(1, 5))
                {
                case 1:
                    entities.push_back(new PlanetEarthEntity(
                        xMarge + (p_size / 2) + (x*(p_size * 2)),
                        yMarge + (p_size / 2) + (y*(p_size * 2)),
                        { 255, 255, 255, 255 },
                        p_size,
                        p_size,
                        atmosphereM["earth"]
                    ));
                    break;
                case 2:
                    entities.push_back(new PlanetSandEntity(
                        xMarge + (p_size / 2) + (x*(p_size * 2)),
                        yMarge + (p_size / 2) + (y*(p_size * 2)),
                        { 255, 255, 255, 255 },
                        p_size,
                        p_size,
                        atmosphereM["sand"]
                    ));
                    break;
                case 3:
                    entities.push_back(new PlanetToxicEntity(
                        xMarge + (p_size / 2) + (x*(p_size * 2)),
                        yMarge + (p_size / 2) + (y*(p_size * 2)),
                        { 255, 255, 255, 255 },
                        p_size,
                        p_size,
                        atmosphereM["toxic"]
                    ));
                    break;
                case 4:
                    entities.push_back(new PlanetMoonEntity(
                        xMarge + (p_size / 2) + (x*(p_size * 2)),
                        yMarge + (p_size / 2) + (y*(p_size * 2)),
                        { 255, 255, 255, 255 },
                        p_size,
                        p_size
                    ));
                    break;
                default:
                    break;
                }
            }

        }

        return entities;
    }

    void PlanetFactory::sceneEnd(std::vector<Entity*> entities)
    {
    }
}


