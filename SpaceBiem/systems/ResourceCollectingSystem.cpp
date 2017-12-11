
#include "ResourceCollectingSystem.h"


namespace spacebiem
{
    void ResourceCollectingSystem::update(const Entity & entity)
    {
        if (!entity.isTag("player")) return;

        auto cc = entity.getComponent<CollidableComponent>("collidable");

        for (const auto & collideInfo : cc->getCollisions()) {
            auto bonus = collideInfo.entity;

            if (collideInfo.entity->isTag("resource")) {
                auto rbc = bonus->getComponent<ResourceBonusComponent>("resourcebonus");
                auto sbc = bonus->getComponent<ScoreBonusComponent>("scorebonus");
                auto rc = entity.getComponent<ResourceComponent>("resources");
                auto sc = entity.getComponent<ScoreComponent>("score");

                rc->addResource(rbc->getName(), rbc->getAmount());
                sc->addScore(sbc->getScoreBonus());

                bonus->die();
            }
        }
    }
}
