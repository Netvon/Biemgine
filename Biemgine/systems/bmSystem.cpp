#include "stdafx.h"
#include "..\systems\bmSystem.h"
#include "..\managers\bmStateManager.h"

namespace biemgine
{
    bmSystem::~bmSystem() {}
    void bmSystem::before() {}
    void bmSystem::before(const float deltaTime) {}
    void bmSystem::update(const bmEntity & entity) {}
    void bmSystem::update(const bmEntity & entity, const float deltaTime) {}
    void bmSystem::after() {}
    void bmSystem::after(const float deltaTime) {}
    void bmSystem::setTransitionManager(const bmStateManager * pManager)
    {
        transitionManager = pManager;
    }

    const bmStateManager* bmSystem::getTransitionManager() const
    {
        return transitionManager;
    }
}
