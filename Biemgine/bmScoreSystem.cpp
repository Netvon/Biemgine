#include "stdafx.h"
#include "bmScoreSystem.h"
#include "bmScoreComponent.h"


bmScoreSystem::bmScoreSystem()
{
}


bmScoreSystem::~bmScoreSystem()
{
}

void bmScoreSystem::update(const bmEntity& entity, const float deltaTime)
{
    if (!entity.hasComponent("score")) {
        return;
    }

    auto sc = entity.getComponent<bmScoreComponent*>("score");

    sc->addScore(deltaTime / 180);

    std::cout << "Score: " << sc->getScore() << std::endl;
}

void bmScoreSystem::onSceneSwitch()
{
}
