#include <algorithm>

#include "GameoverSystem.h"

namespace spacebiem
{

    void GameoverSystem::update(const Entity & entity)
    {
        auto oc = entity.getComponent<OxygenComponent*>("oxygen");
        if (!entity.hasComponent("oxygen") ||
            entity.hasComponent("ui") ||
            oc->getOxygenAmount() > oc->getOxygenScale())
            return;


        int score = 0;
        map<string, int> resources = map<string, int>();
        map<string, int> planetsScore = map<string, int>({ { "earth",0 },{ "sand",0 },{ "moon",0 },{ "toxic",0 } });

        if (entity.hasComponent("score")) {
            auto sc = entity.getComponent<ScoreComponent*>("score");
            score = sc->getScore();
        }
        if (entity.hasComponent("resources")) {
            auto rc = entity.getComponent<ResourceComponent*>("resources");
            resources = rc->getResources();
        }
        if (entity.hasComponent("collidable")) {
            auto cc = entity.getComponent<CollidableComponent*>("collidable");
            for (auto c : cc->getCollisions()) {
                auto planet = getStateManager()->getEntity(c.first);

                if (planet == nullptr || !planet->hasComponent("scorebonus")) continue;

                auto sb = planet->getComponent<ScoreBonusComponent*>("scorebonus");

                if (sb->isScoreGiven()) {
                    planetsScore[planet->getTag()]++;
                }
            }
        }        

        getStateManager()->navigateTo<GameoverScene>(score, resources, planetsScore);
    }



}
