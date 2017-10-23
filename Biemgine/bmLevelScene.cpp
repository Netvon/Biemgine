#include "stdafx.h"
#include "bmLevelScene.h"
#include "bmPlayerEntity.h"
#include "bmSurfaceEntity.h"
#include "bmPlanetEarthEntity.h"
#include "bmPlanetMoonEntity.h"
#include "bmOxygenUIEntity.h"
#include "bmScoreUIEntity.h"

void bmLevelScene::sceneCreated()
{
    cout << "LevelScene created" << endl;

    // Setup the scene with entities

    /*for (size_t i = 0; i < 6; i++)
    {
        int x = (i * 30) + 300;

        for (size_t z = 0; z < 3; z++)
        {
            int y = (z * 50);
            getEntityManager().addEntity(new bmPlayerEntity(x, y, 255, 255, 255, 15 * 2, 25 * 2));
        }
    }*/


    float width = 15 * 2;
    float height = 25 * 2;

    //for (float x = 100; x < 700; x += width + width/4.0f)
    //{
    //    for (float y = -height * 3; y < 50; y += height + height / 4.0f)
    //    {
    //        getEntityManager().addEntity(new bmPlayerEntity(x, y, { 255, 255, 255, 255 }, width, height));
    //    }        
    //}

    getEntityManager().addEntity(new bmPlayerEntity(800, 100, { 255, 255, 255, 255 }, width, height));

    int wW = getTransitionManager().getWindowWidth();
    int wH = getTransitionManager().getWindowHeight();
    int xMarge = 60;
    float p_size = (wW/4)-(xMarge/2);
    int yMarge = (wH-(p_size*2))/2;

    getEntityManager().addEntity(new bmOxygenUIEntity());
    getEntityManager().addEntity(new bmScoreUIEntity());

    getEntityManager().addEntity(new bmPlanetEarthEntity(xMarge + (p_size / 2), yMarge + (p_size / 2), { 255, 255, 255, 255 }, p_size, p_size));
    getEntityManager().addEntity(new bmPlanetMoonEntity(xMarge + (p_size / 2) + (p_size * 2), yMarge + (p_size / 2), { 255, 255, 255, 255 }, p_size, p_size));

}

void bmLevelScene::input()
{
    if (im.isKeyDown("Q")) {
        signalQuit();
    }

    if (im.isKeyDown("A")) {
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
