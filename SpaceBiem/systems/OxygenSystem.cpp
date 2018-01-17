#include <algorithm>

#include "OxygenSystem.h"

namespace spacebiem
{
    void OxygenSystem::onAddEntity(Entity & entity)
    {
        if (entity.hasComponent("atmosphere"))
        {
            PlanetEntry planetEntry;
            planetEntry.entity = &entity;
            planetEntry.positionComponent = entity.getComponent<PositionComponent>("position");
            planetEntry.AtmosphereComponent = entity.getComponent<AtmosphereComponent>("atmosphere");
            planetEntry.audioComponent = entity.getComponent<AudioComponent>("audio");

            planetEntries.push_back(std::move(planetEntry));
        }

        if (!entity.hasComponent("ui") && entity.hasComponent("oxygen"))
        {
            PlayerEntry playerEntry;
            playerEntry.entity = &entity;
            playerEntry.positionComponent = entity.getComponent<PositionComponent>("position");
            playerEntry.collidableComponent = entity.getComponent<CollidableComponent>("collidable");
            playerEntry.oxygenComponent = entity.getComponent<OxygenComponent>("oxygen");

            playerEntries.push_back(std::move(playerEntry));
        }
    }

    void OxygenSystem::update()
    {
        for (const PlayerEntry& player : playerEntries)
        {
            if (currentPlanetEntry == nullptr)
            {
                for (const PlanetEntry& planet : planetEntries)
                {
                    if (!planet.entity->getIsOnScreen()) continue;

                    int xA = planet.AtmosphereComponent->getX();
                    int yA = planet.AtmosphereComponent->getY();
                    int rA = planet.AtmosphereComponent->getRadius();
                    int x = player.positionComponent->getX();
                    int y = player.positionComponent->getY();

                    if (((x - xA)*(x - xA)) + ((y - yA)*(y - yA)) <= (rA*rA))
                    {
                        if (planet.audioComponent != nullptr)
                        {
                            getStateManager()->getAudioDevice().playFadeInSoundEffect(planet.audioComponent->getPath(), planet.audioComponent->getLoops(), planet.audioComponent->getChannel(), planet.audioComponent->getVolume(), planet.audioComponent->getFadeInTime());
                        }

                        currentPlanetEntry = std::make_shared<PlanetEntry>(planet);
                    }
                }
            }
            else
            {
                int xA = currentPlanetEntry->AtmosphereComponent->getX();
                int yA = currentPlanetEntry->AtmosphereComponent->getY();
                int rA = currentPlanetEntry->AtmosphereComponent->getRadius();
                int x = player.positionComponent->getX();
                int y = player.positionComponent->getY();

                if (!(((x - xA)*(x - xA)) + ((y - yA)*(y - yA)) <= (rA*rA)))
                {
                    if (currentPlanetEntry->audioComponent != nullptr)
                    {
                        getStateManager()->getAudioDevice().fadeOutSoundEffect(currentPlanetEntry->audioComponent->getPath(), currentPlanetEntry->audioComponent->getFadeInTime());
                    }

                    currentPlanetEntry = nullptr;
                }
            }

            float oAmount = player.oxygenComponent->getOxygenAmount();

            if (currentPlanetEntry == nullptr)
            {
                oAmount -= player.oxygenComponent->getOxygenScale();
            }
            else
            {
                oAmount += (currentPlanetEntry->AtmosphereComponent->getOxygenModifier() * player.oxygenComponent->getOxygenScale());
            }

            // you're being attacked by an AI, it grabs you by the neck!!
            if (player.collidableComponent != nullptr)
            {
                for (const auto & collideInfo : player.collidableComponent->getCollisions())
                {
                    if (collideInfo.entity->isTag("ai"))
                    {
                        oAmount -= 40.0f;
                    }
                }
            }

            player.oxygenComponent->setOxygenAmount(oAmount);

        }
    }

    
}
