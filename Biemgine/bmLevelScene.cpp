#include "stdafx.h"
#include "bmLevelScene.h"
#include "bmPlayerEntity.h"
#include "bmSurfaceEntity.h"
#include "bmPlanetEarthEntity.h"
#include "bmPlanetMoonEntity.h"
#include "bmOxygenUIEntity.h"
#include "bmScoreUIEntity.h"
#include "bmScoreUIFactory.h"

void bmLevelScene::sceneCreated()
{

    float width = 15 * 2;
    float height = 25 * 2;

    getEntityManager().addEntity(new bmPlayerEntity(800, 500, { 255, 255, 255, 255 }, width, height));

    int wW = getTransitionManager().getWindowWidth();
    int wH = getTransitionManager().getWindowHeight();
    int xMarge = 60;
    float p_size = (wW / 4) - (xMarge / 2);
    int yMarge = (wH - (p_size * 2)) / 2;

    getEntityManager().addEntity(new bmOxygenUIEntity());
    getEntityManager().addEntity(new bmScoreUIEntity());

    getEntityManager().addEntity(new bmPlanetEarthEntity(xMarge + (p_size / 2), yMarge + (p_size / 2), { 255, 255, 255, 255 }, p_size, p_size));
    getEntityManager().addEntity(new bmPlanetMoonEntity(xMarge + (p_size / 2) + (p_size * 2), yMarge + (p_size / 2), { 255, 255, 255, 255 }, p_size, p_size));

}

void bmLevelScene::sceneEnd() {

    bmScoreUIFactory sf;
    sf.sceneEnd(getEntityManager().getEntities());

}


void bmLevelScene::input()
{
    if (im.isKeyDown("Q")) {
        signalQuit();
    }

    if (im.isKeyDown("Escape")) {
        getTransitionManager().quitLevelTransition();
    }

    if (im.isKeyDown("P")) {
        if (!isPauseButtonDown) {

            if (getTransitionManager().isPaused()) getTransitionManager().resumeGame();
            else getTransitionManager().pauseGame();
            
            isPauseButtonDown = true;
        }
    }
    else {
        isPauseButtonDown = false;
    }
    
}

void bmLevelScene::update()
{
    if (!getTransitionManager().isPaused()) {
        updateEntities();
    }
}

void bmLevelScene::render(const float deltaTime)
{
    getTransitionManager().drawBackground();
    updateEntities(deltaTime);
    getTransitionManager().drawOverlay();
}
