#include "stdafx.h"
#include "bmTransitionManager.h"
#include "bmSceneManager.h"



void bmTransitionManager::gameOverTransition()
{
    cout << "GAME OVER" << endl;
    sceneManager->changeScene(bmScene_menu);
}

void bmTransitionManager::quitLevelTransition()
{
    sceneManager->changeScene(bmScene_menu);
}

void bmTransitionManager::startLevelTransition()
{
    sceneManager->changeScene(bmScene_level);
}
