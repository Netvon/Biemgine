#include "stdafx.h"
#include "bmMenuScene.h"
#include "bmSpriteEntity.h"


void bmMenuScene::sceneCreated()
{
    /*bmRectangle* c1 = new bmRectangle(0, 0, 100, 100);
    addComponent(c1);*/

    getEntityManager().addEntity(new bmSpriteEntity("textures/biemlogo.png", 800 / 2 - 50, 600 / 2 - 56/2, { 255, 255, 255, 255 }, -1, -1));


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
