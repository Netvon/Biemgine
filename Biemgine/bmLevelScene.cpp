#include "stdafx.h"
#include "bmLevelScene.h"
#include "bmSceneManager.h"
#include "bmPlayerEntity.h"
#include "bmSurfaceEntity.h"
#include "bmPlanetEntity.h"
#include "bmPlanetEarthEntity.h"


void bmLevelScene::sceneCreated()
{
    //bmRectangle* c1 = new bmRectangle(0, 0, 100, 100);
    //addComponent(c1);

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

    float width = 45 / 2;
    float height = 45 / 2;

    for (float x = 100; x < 700; x += width + width/4.0f)
    {
        for (float y = -height * 3; y < 50; y += height + height / 4.0f)
        {
            getEntityManager().addEntity(new bmPlayerEntity(x, y, { 255, 255, 255, 255 }, width, height));
        }
        
    }


    
    /*getEntityManager().addEntity(new bmPlayerEntity(300, 25, { 255, 255, 255 }, 15 * 2, 25 * 2));

    getEntityManager().addEntity(new bmPlayerEntity(400, 25, { 255, 255, 255 }, 15 * 2, 25 * 2));
    getEntityManager().addEntity(new bmPlayerEntity(500, 25, { 255, 255, 255 }, 15 * 2, 25 * 2));
    getEntityManager().addEntity(new bmPlayerEntity(600, 25, { 255, 255, 255 }, 15 * 2, 25 * 2));*/

    
    //getEntityManager().addEntity(new bmPlayerEntity(10, 25, 255, 255, 255, 15, 25));
    //getEntityManager().addEntity(new bmPlayerEntity(20, 50, 255, 255, 255, 15, 25));
    //getEntityManager().addEntity(new bmPlayerEntity(100, 100, 0, 255, 0, 15, 25));
    //getEntityManager().addEntity(new bmPlayerEntity(200, 200, 0, 0, 255, 15, 25));


    //bottom
    //getEntityManager().addEntity(new bmSurfaceEntity(0, 580, { 255, 255, 255 }, 800, 20));

    //top
    //getEntityManager().addEntity(new bmSurfaceEntity(0, 0, { 255, 255, 255 }, 800, 20));

    //left
    //getEntityManager().addEntity(new bmSurfaceEntity(0, 0, { 255, 255, 255 }, 20, 600));

    //right
    //getEntityManager().addEntity(new bmSurfaceEntity(780, 0, { 255, 255, 255 }, 20, 600));

    float p_size = 300.f;
    float p_size_h = p_size * 0.5f;

    getEntityManager().addEntity(new bmPlanetEarthEntity(400 - p_size_h, 300 - p_size_h, { 255, 255, 255, 255 }, p_size, p_size));

    // Create and add Player
    // Create and add Planets
}

void bmLevelScene::input()
{
    if (im.isKeyDown("Q")) {
        signalQuit();
    }

    if (im.isKeyDown("A")) {
        getSceneManager().changeScene(bmScene_menu);
    }

    if (im.isKeyDown(",")) {
        isPaused = true;
    }
    if (im.isKeyDown(".")) {
        isPaused = false;
    }

}

void bmLevelScene::update()
{
    if (!isPaused) {
        updateEntities();
    }
}

void bmLevelScene::render(const float deltaTime)
{

    updateEntities(deltaTime);
}
