#include "stdafx.h"
#include "bmLevelScene.h"
#include "bmSceneManager.h"
#include "bmPlayerEntity.h"
#include "bmSurfaceEntity.h"
#include "bmPlanetEarthEntity.h"
#include "bmOxygenUIEntity.h"


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

    float width = 45 / 2;
    float height = 45 / 2;

    /*for (float x = 100; x < 700; x += width + width/4.0f)
    {
        for (float y = -height * 3; y < 50; y += height + height / 4.0f)
        {
            getEntityManager().addEntity(new bmPlayerEntity(x, y, { 255, 255, 255, 255 }, width, height));
        }
        
    }*/

    getEntityManager().addEntity(new bmPlayerEntity(100, 50, { 255, 255, 255 }, width, height));

    float p_size = 400.f;
    float p_size_h = p_size * 0.5f;

    getEntityManager().addEntity(new bmPlanetEarthEntity(400 - p_size_h, 300 - p_size_h, { 255, 255, 255, 255 }, p_size, p_size));


    getEntityManager().addEntity(new bmOxygenUIEntity());


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
