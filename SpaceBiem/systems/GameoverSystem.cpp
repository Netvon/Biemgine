#include <algorithm>

#include "GameoverSystem.h"

using biemgine::FileHandler;

namespace spacebiem
{
    void GameoverSystem::update(const Entity & entity)
    {
        if (!entity.hasComponent("oxygen")
            || entity.hasComponent("ui")) {
            return;
        }

        auto oc = entity.getComponent<OxygenComponent>("oxygen");

        if (oc->getOxygenAmount() > oc->getOxygenScale()) {
            return;
        }

        int score = 0;
        map<string, int> resources = map<string, int>();
        map<string, int> planetsScore = map<string, int>({ { "earth",0 },{ "sand",0 },{ "moon",0 },{ "toxic",0 },{ "ice",0 } });

        if (entity.hasComponent("score")) {
            auto sc = entity.getComponent<ScoreComponent>("score");
            score = sc->getScore();
        }

        if (entity.hasComponent("resources")) {
            auto rc = entity.getComponent<ResourceComponent>("resources");
            resources = rc->getResources();
        }

        if (entity.hasComponent("collidable")) {
            auto cc = entity.getComponent<CollidableComponent>("collidable");

            for (auto c : cc->getCollisions()) {
                auto planet = getStateManager()->getEntity(c.first);

                if (planet == nullptr || !planet->hasComponent("scorebonus")) continue;

                auto sbc = planet->getComponent<ScoreBonusComponent>("scorebonus");

                if (sbc->isScoreGiven()) {
                    planetsScore[planet->getTag()]++;
                }
            }
        }

        FileHandler fileHandler{""};
        fileHandler.remove("data/savegame.csv");

        getStateManager()->navigateTo<GameoverScene>(score, resources, planetsScore);
    }
}
