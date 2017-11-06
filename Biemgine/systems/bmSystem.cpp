#include "..\stdafx.h"
#include "..\systems\bmSystem.h"
#include "..\managers\bmStateManager.h"

void bmSystem::setTransitionManager(bmStateManager * pManager)
{
    transitionManager = pManager;
}
