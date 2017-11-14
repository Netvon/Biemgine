#include "Biemgine.h"
#include "ResourceFactory.h"


namespace spacebiem
{
    ResourceFactory::ResourceFactory()
    {
        FileParser fileParser;
        spawnRates = fileParser.resourceSpawnRateContent();
        scores = fileParser.resourceScoreContent();
    }
    vector<Entity*> ResourceFactory::sceneStart(int windowW, int windowH)
    {
        return vector<Entity*>();
    }

    void ResourceFactory::sceneEnd(std::vector<Entity*> entities)
    {
    }

    vector<ResourceEntity*> ResourceFactory::getPlanetResources(int x, int y, int r, string planet)
    {
        vector<ResourceEntity*> resources;

        int w = 30;
        int h = 30;

        map<string, vector<float>> spawnResources = spawnRates[planet];
        for each(auto sr in spawnResources) {
            for (int i = RandomGenerator::getInstance().generate(sr.second[0], sr.second[1]); i > 0; i--) {

                if (RandomGenerator::getInstance().generate(0, 100) > sr.second[2] * 100) continue;

                float angle = static_cast<float>(RandomGenerator::getInstance().generate(1, 100)) / 100 * 3.1415926535897f * 2;
                float cX = cos(angle)*r;
                float cY = sin(angle)*r;

                resources.push_back(new ResourceEntity(x + cX, y + cY, { 255,255,255,255 }, w, h, sr.first, scores[sr.first]));

            }
        }

        return resources;
    }

}


