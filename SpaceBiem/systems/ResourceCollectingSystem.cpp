
#include "ResourceCollectingSystem.h"


namespace spacebiem
{
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
        for (auto& entity : resource)
        {
            auto cc = entity->getComponent<CollidableComponent>("collidable");

            for (auto& bonus : resourceBonus)
            {
                if (cc->collides(*bonus)) {
                    auto rbc = bonus->getComponent<ResourceBonusComponent>("resourcebonus");
                    auto sbc = bonus->getComponent<ScoreBonusComponent>("scorebonus");
                    auto rc = entity->getComponent<ResourceComponent>("resources");
                    auto sc = entity->getComponent<ScoreComponent>("score");

                    rc->addResource(rbc->getName(), rbc->getAmount());
                    sc->addScore(sbc->getScoreBonus());

                    bonus->die();
                }
            }
        }

        resource.clear();
        resourceBonus.clear();
    }

    System::required_components ResourceCollectingSystem::requirements() const
    {
        return {
            System::requirement<CollidableComponent>(),
        };
    }
}
