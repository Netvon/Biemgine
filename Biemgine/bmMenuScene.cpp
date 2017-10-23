#include "stdafx.h"
#include "bmMenuScene.h"
#include "bmSpriteEntity.h"
#include "bmScoreUIEntity.h"


void bmMenuScene::sceneCreated()
{
    /*bmRectangle* c1 = new bmRectangle(0, 0, 100, 100);
    addComponent(c1);*/

    int w = 50;
    int x = getTransitionManager().getWindowWidth() / 2 - w;


    getEntityManager().addEntity(new bmSpriteEntity("textures/biemlogo.png", x, 100, { 255, 255, 255, 255 }, -1, -1));


    for (int y = 200; y < 500; y += 25) {
        getEntityManager().addEntity(new bmScoreUIEntity(x, y, 60));
    }



    cout << "MenuScene created" << endl;
}


void bmMenuScene::input()
{
    if (im.isKeyDown("Q")) {
        signalQuit();
    }

    if (im.isKeyDown("S")) {
        getTransitionManager().startLevelTransition();
    }
}

void bmMenuScene::update()
{

    updateEntities();
}

void bmMenuScene::render(const float deltaTime)
{

    updateEntities(deltaTime);
}
