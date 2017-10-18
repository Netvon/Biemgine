#include "stdafx.h"
#include "bmOxygenSystem.h"

void bmOxygenSystem::before()
{
}

void bmOxygenSystem::update(const bmEntity & entity)
{
    if (!entity.hasComponent("oxygen")) return;
    if (entity.hasComponent("ui")) return;

    auto oc = entity.getComponent<bmOxygenComponent*>("oxygen");


    // check if it is on a planet without atmosphere
    // Then:
    int oAmount = oc->getOxygenAmount();
    oAmount -= oc->getOxygenDecrease();
    oc->setOxygenAmount(oAmount);

    // Else: TODO Add oxygen to the component


    // Do something more later with modifiers and upgrades (0.5 decrease if mask upgraded)


    if (oAmount <= 0) {
        transitionManager->gameOverTransition();
    }
}

void bmOxygenSystem::after()
{
}

void bmOxygenSystem::onSceneSwitch()
{
}


