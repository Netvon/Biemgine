#include "ResourceCollectingSystem.h"

namespace spacebiem
{
    void ResourceCollectingSystem::onAddEntity(Entity & entity)
    {
        if (!entity.isTag("player")) return;

        PlayerEntry playerEntry;
        playerEntry.collidableComponent = entity.getComponent<CollidableComponent>("collidable");
        playerEntry.resourceComponent = entity.getComponent<ResourceComponent>("resources");
        playerEntry.scoreComponent = entity.getComponent<ScoreComponent>("score");

        playerEntries.push_back(std::move(playerEntry));
    }

    void ResourceCollectingSystem::update()
    {
        for (const PlayerEntry& player : playerEntries)
        {
            for (const auto & collideInfo : player.collidableComponent->getCollisions())
            {
                auto bonus = collideInfo.entity;

                if (collideInfo.entity->isTag("resource") && collideInfo.entity->isAlive())
                {
                    auto rbc = bonus->getComponent<ResourceBonusComponent>("resourcebonus");
                    auto sbc = bonus->getComponent<ScoreBonusComponent>("scorebonus");
                    auto rc = player.resourceComponent;
                    auto sc = player.scoreComponent;
                    auto ac = bonus->getComponent<AudioComponent>("audio");

                    rc->addResource(rbc->getName(), rbc->getAmount());
                    sc->addScore(sbc->getScoreBonus());

                    if (ac != nullptr)
                        getStateManager()->getAudioDevice().playSoundEffect(ac->getPath(), ac->getLoops(), ac->getChannel(), ac->getVolume());

                    bonus->die();
                }
            }
        }
    }
}
