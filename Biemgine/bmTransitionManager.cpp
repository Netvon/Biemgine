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

int bmTransitionManager::getWindowWidth() const
{    
    return window->getWidth();
}

int bmTransitionManager::getWindowHeight() const
{
    return window->getHeight();
}
