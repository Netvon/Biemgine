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

        // Meer condities

        int score = 0;
        map<string, int> resources = map<string, int>();
        map<string, int> planetsScore = map<string, int>();

        if (entity.hasComponent("score")) {
            auto sc = entity.getComponent<ScoreComponent*>("score");
            score = sc->getScore();
        }
        if (entity.hasComponent("resources")) {
            auto rc = entity.getComponent<ResourceComponent*>("resources");
            resources = rc->getResources();
        }
        

        // Pak alle zooi en geef die mee met de navigate
        

        getStateManager()->navigateTo<GameoverScene>(score, resources, planetsScore);
    }



}
