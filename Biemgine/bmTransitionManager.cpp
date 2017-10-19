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

void bmTransitionManager::pauseGame()
{
    paused = true;

}

void bmTransitionManager::resumeGame()
{
    paused = false;
}

bool bmTransitionManager::isPaused()
{
    return paused;
}

void bmTransitionManager::drawOverlay()
{
    if (paused) {
        auto gd = window->getGraphicsDevice();

        int x = 20;
        int y = 30;

        //gd->drawSquare(0,0,getWindowWidth()/2,getWindowHeight()/2, { 0, 0, 0, 20 });

        gd->drawText("The game is paused.", x, y, { 255, 255, 255, 255 }, 20);
        gd->drawText("Press 'P' to resume the game...", x, y + 25, { 255, 255, 255, 255 }, 20);


    }
}
