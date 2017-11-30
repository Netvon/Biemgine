#include "stdafx.h"
#include "..\systems\System.h"
#include "..\managers\StateManager.h"

namespace biemgine
{
    System::~System() {}
    void System::before() {}
    //void System::before(const float deltaTime) {}
    void System::update(const Entity & entity) {}
    void System::update(const Entity & entity, const float deltaTime) {}
    void System::after() {}
    void System::after(const float deltaTime) {}
    void System::setStateManager(StateManager * pManager)
    {
        stateManager = pManager;
    }

    StateManager* System::getStateManager()
    {
        return stateManager;
    }
}
