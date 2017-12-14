#include "stdafx.h"
#include "..\systems\System.h"
#include "..\managers\StateManager.h"

namespace biemgine
{
    System::~System() {}
    inline void System::onAddEntity(Entity & entity) {}
    inline void System::before() {}
    inline void System::before(const float deltaTime) {}
    inline void System::update() {}
    inline void System::update(const float deltaTime) {}
    inline void System::update(const Entity & entity) {}
    inline void System::update(const Entity & entity, const float deltaTime) {}
    inline void System::after() {}
    inline void System::after(const float deltaTime) {}

    void System::setStateManager(StateManager * pManager)
    {
        stateManager = pManager;
    }

    StateManager* System::getStateManager()
    {
        return stateManager;
    }

    void System::setTimeout(int pTimeout) {
        timeout = pTimeout;
        timeoutCounter = 0;
    }

    void System::nextUpdate() {
        if (timeoutCounter == timeout)
            timeoutCounter = 0;
        else
            timeoutCounter++;
    }

    bool System::hasTimedOut() {
        return timeoutCounter != 0;
    }
}
