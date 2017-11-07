#include "stdafx.h"
#include "..\systems\bmSystem.h"
#include "..\managers\bmStateManager.h"

namespace biemgine {
    void bmSystem::setTransitionManager(const bmStateManager * pManager)
    {
        transitionManager = pManager;
    }
}
