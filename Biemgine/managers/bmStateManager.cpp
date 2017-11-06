#include "..\..\stdafx.h"
#include "bmStateManager.h"
#include "bmSceneManager.h"

bmStateManager::~bmStateManager()
{

}

void bmStateManager::gameOverTransition()
{
    sceneManager->changeScene(bmScene_menu);
}

void bmStateManager::quitLevelTransition()
{
    sceneManager->changeScene(bmScene_menu);
}

void bmStateManager::startLevelTransition()
{
    sceneManager->changeScene(bmScene_level);
}

int bmStateManager::getWindowWidth() const
{    
    return window->getWidth();
}

int bmStateManager::getWindowHeight() const
{
    return window->getHeight();
}

void bmStateManager::pauseGame()
{
    paused = true;

}

void bmStateManager::resumeGame()
{
    paused = false;
}

bool bmStateManager::isPaused()
{
    return paused;
}

void bmStateManager::drawOverlay()
{
    if (paused) {
        auto gd = window->getGraphicsDevice();

        int x = 20;
        int y = 60;

        gd->drawText("The game is paused.", x, y, { 255, 255, 255, 255 }, 20);
        gd->drawText("Press 'P' to resume the game...", x, y + 25, { 255, 255, 255, 255 }, 20);
    }
}

void bmStateManager::drawBackground() {

    auto gd = window->getGraphicsDevice();

    gd->drawTexture("textures/space.png", 0, 0, getWindowWidth(), getWindowHeight(), 0.f, { 255, 255, 255, 255 });

}
