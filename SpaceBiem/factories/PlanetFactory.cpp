#include "Biemgine.h"
#include "PlanetFactory.h"

namespace spacebiem
{
    vector<Entity*> PlanetFactory::sceneStart(int windowW, int windowH)
    {
        vector<Entity*> entities;


        int xMarge = 60;
        float p_size = (windowW / 4) - (xMarge / 2);
        int yMarge = (windowH - (p_size * 2)) / 2;


        FileHandler fh;
        map<string, int> atmosphereM = fh.atmosphereContent();

        entities.push_back(new PlanetEarthEntity(
            xMarge + (p_size / 2),
            yMarge + (p_size / 2),
            { 255, 255, 255, 255 },
            p_size,
            p_size,
            atmosphereM["earth"]
        ));

        entities.push_back(new PlanetMoonEntity(
            xMarge + (p_size / 2) + (p_size * 2),
            yMarge + (p_size / 2),
            { 255, 255, 255, 255 },
            p_size,
            p_size
        ));


        return entities;
    }

    void PlanetFactory::sceneEnd(std::vector<Entity*> entities)
    {
    }
}


