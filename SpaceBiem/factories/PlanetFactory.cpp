#include "Biemgine.h"
#include "PlanetFactory.h"

namespace spacebiem
{
    void PlanetFactory::create(const string& type, int pX, int pY, int width, int height, std::shared_ptr<EntityManager> entityManager, ResourceFactory resourceFactory , NameGenerator nameGenerator, map<string, float> atmosphereM, map<string, int> scoreBonus)
    {
        if (type == "moon") {
            entityManager->addEntity<PlanetMoonEntity>(pX, pY, Color::White(), width, height, scoreBonus["moon"], nameGenerator.getName());
            resourceFactory.generatePlanetResources(pX + (width / 2), pY + (height / 2), height / 2, "moon", entityManager);
        }
        else if (type == "earth") {
            entityManager->addEntity<PlanetEarthEntity>(pX, pY, Color::EarthAtmosphere(), width, height, scoreBonus["earth"], atmosphereM["earth"], nameGenerator.getName());
            resourceFactory.generatePlanetResources(pX + (width / 2), pY + (height / 2), height / 2, "earth", entityManager);
        }
        else if (type == "sand") {
            entityManager->addEntity<PlanetSandEntity>(pX, pY, Color::SandAtmosphere(), width, height, scoreBonus["sand"], atmosphereM["sand"], nameGenerator.getName());
            resourceFactory.generatePlanetResources(pX + (width / 2), pY + (height / 2), height / 2, "sand", entityManager);
        }
        else if (type == "toxic") {
            entityManager->addEntity<PlanetToxicEntity>(pX, pY, Color::ToxicAtmosphere(), width, height, scoreBonus["toxic"], atmosphereM["toxic"], nameGenerator.getName());
            resourceFactory.generatePlanetResources(pX + (width / 2), pY + (height / 2), height / 2, "toxic", entityManager);
        }
    }

    void PlanetFactory::load(const string& type, int pX, int pY, int width, int height, std::shared_ptr<EntityManager> entityManager, string name, map<string, float> atmosphereM, int planetScore, bool isDiscovered, vector<float> flagComponent)
    {
        int id;

        if (type == "moon") {
            id = entityManager->addEntity<PlanetMoonEntity>(pX, pY, Color::White(), width, height, planetScore, name);
        }
        else if (type == "earth") {
            id = entityManager->addEntity<PlanetEarthEntity>(pX, pY, Color::EarthAtmosphere(), width, height, planetScore, atmosphereM["earth"], name);
        }
        else if (type == "sand") {
            id = entityManager->addEntity<PlanetSandEntity>(pX, pY, Color::SandAtmosphere(), width, height, planetScore, atmosphereM["sand"], name);
        }
        else if (type == "toxic") {
            id = entityManager->addEntity<PlanetToxicEntity>(pX, pY, Color::ToxicAtmosphere(), width, height, planetScore, atmosphereM["toxic"], name);
        }

        auto planet = entityManager->getEntity(id);

        if (isDiscovered) {
            auto texts = planet->getComponents<TextComponent*>("text");
            for (auto text : texts) {
                text->setVisible(true);
            }
        }

        if (!flagComponent.empty()) {
            auto components = planet->getComponents<TextureComponent*>("texture");

            for (auto it = components.begin(); it != components.end(); ++it)
            {
                auto component = (*it);
                if (component->getTag() != "flag") continue;

                auto planetP = planet->getComponent<PositionComponent*>("position");

                component->setOffsetX(flagComponent[0]);
                component->setOffsetY(flagComponent[1]);
                component->setRotation(flagComponent[2]);
                component->setVisible(true);
            }
        }

    }
}
