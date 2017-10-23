#include "stdafx.h"
#include "bmScoreSystem.h"
#include "bmScoreComponent.h"
#include "bmLoop.h"

extern const float BM_GAMELOOP_UPDATE_MS;

bmScoreSystem::bmScoreSystem()
{
}

bmScoreSystem::~bmScoreSystem()
{
}

void bmScoreSystem::update(const bmEntity& entity, const float deltaTime)
{
    if (!entity.hasComponent("score")) return;
    if (entity.hasComponent("ui")) return;
    auto sc = entity.getComponent<bmScoreComponent*>("score");

    sc->addScore(deltaTime / 600);
}

void bmScoreSystem::onSceneSwitch()
{
}
