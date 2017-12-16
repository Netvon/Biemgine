#include <algorithm>

#include "GameoverSystem.h"

using biemgine::FileHandler;

namespace spacebiem
{
    void GameoverSystem::onAddEntity(Entity & entity)
    {
        if (!entity.hasComponent("ui") && entity.hasComponent("oxygen") && entity.hasComponent("score") && entity.hasComponent("resources") && entity.hasComponent("collidable") && entity.hasComponent("grounded"))
        {
            auto pc = entity.getComponent<PositionComponent>("position");
            auto gc = entity.getComponent<GroundedComponent>("grounded");
            auto oc = entity.getComponent<OxygenComponent>("oxygen");
            auto sc = entity.getComponent<ScoreComponent>("score");
            auto rc = entity.getComponent<ResourceComponent>("resources");
            auto cc = entity.getComponent<CollidableComponent>("collidable");

            PlayerEntry playerEntry;
            playerEntry.entity = &entity;
            playerEntry.positionComponent = pc;
            playerEntry.groundedComponent = gc;
            playerEntry.oxygenComponent = oc;
            playerEntry.scoreComponent = sc;
            playerEntry.resourceComponent = rc;
            playerEntry.collidableComponent = cc;

            playerEntries.push_back(std::move(playerEntry));
        }
    }

    void GameoverSystem::update()
    {
        for (const PlayerEntry& player : playerEntries)
        {
            bool gameover = false;

            if (player.groundedComponent->isGrounded())
            {
                auto ground = player.groundedComponent->getGroundedOn();
                if (ground->getTag() == "lava") gameover = true;
            }

            if (player.oxygenComponent->getOxygenAmount() <= player.oxygenComponent->getOxygenScale())
                gameover = true;

            if (gameover)
            {
                int score = player.scoreComponent->getScore();
                map<string, int> resources = player.resourceComponent->getResources();
                map<string, int> planetsScore = map<string, int>({{"earth", 0}, {"sand", 0}, {"moon", 0}, {"toxic", 0}, {"ice", 0}});

                for (const auto & collideInfo : player.collidableComponent->getAllCollisions())
                {
                    auto planet = collideInfo.entity;

                    if (!planet->hasComponent("scorebonus")) continue;

                    auto sbc = planet->getComponent<ScoreBonusComponent>("scorebonus");

                    if (sbc->isScoreGiven())
                    {
                        planetsScore[planet->getTag()]++;
                    }
                }

                FileHandler fileHandler{""};
                fileHandler.remove("data/savegame.csv");

                getStateManager()->navigateTo<GameoverScene>(score, resources, planetsScore);
            }
        }  
    }
}
