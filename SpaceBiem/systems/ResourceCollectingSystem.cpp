
#include "ResourceCollectingSystem.h"


namespace spacebiem
{
    void ResourceCollectingSystem::before()
    {
        resource.clear();
        resourceBonus.clear();
    }

    void ResourceCollectingSystem::update(const Entity & entity)
    {

        // player
        if (entity.hasComponent("resources") && entity.hasComponent("collidable"))
        {
            resource.push_back(&entity);
        }

        // resource
        if (entity.hasComponent("resourcebonus") && entity.hasComponent("collidable"))
        {
            resourceBonus.push_back(&entity);
        }

    }

    void ResourceCollectingSystem::after()
    {

        for each (auto entity in resource)
        {
            auto col = entity->getComponent<CollidableComponent*>("collidable");
            for each (auto bonus in resourceBonus)
            {
                if (col->collides(*bonus)) {
                    auto rbc = bonus->getComponent<ResourceBonusComponent*>("resourcebonus");
                    auto sbc = bonus->getComponent<ScoreBonusComponent*>("scorebonus");
                    auto rc = entity->getComponent<ResourceComponent*>("resources");
                    auto sc = entity->getComponent<ScoreComponent*>("score");

                    rc->addResource(rbc->getName(), rbc->getAmount());
                    sc->addScore(sbc->getScoreBonus());

                    bonus->die();
                }
            }
        }

    }
}
