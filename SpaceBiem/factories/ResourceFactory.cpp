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

    void ResourceFactory::generatePlanetResources(int x, int y, int r, string planet, std::shared_ptr<EntityManager> entityManager)
    {
        int w = 30;
        int h = 30;

        map<string, vector<float>> spawnResources = spawnRates[planet];
        for (auto& sr : spawnResources) {
            for (int i = RandomGenerator::getInstance().generate(sr.second[0], sr.second[1]+1); i > 0; i--) {

                if (RandomGenerator::getInstance().generate(0, 100) > sr.second[2] * 100) continue;

                float angle = static_cast<float>(RandomGenerator::getInstance().generate(1, 100)) / 100 * 3.1415926535897f * 2;
                float cX = cos(angle)*r;
                float cY = sin(angle)*r;

                entityManager->addEntity<ResourceEntity>(x + cX, y + cY, Color::White(), w, h, sr.first, scores[sr.first]);
            }
        }
    }

    void ResourceFactory::createPlanetResources(float x, float y, int w, int h, string name, std::shared_ptr<EntityManager> entityManager) {
        entityManager->addEntity<ResourceEntity>(x, y, Color::White(), w, h, name, scores[name]);
    }
}
