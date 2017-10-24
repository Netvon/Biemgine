#include "stdafx.h"
#include "bmMenuScene.h"
#include "bmSpriteEntity.h"
#include "bmScoreUIEntity.h"
#include "bmScoreUIFactory.h"


void bmMenuScene::sceneCreated()
{
    /*bmRectangle* c1 = new bmRectangle(0, 0, 100, 100);
    addComponent(c1);*/

    int wW = getTransitionManager().getWindowWidth();
    int wH = getTransitionManager().getWindowHeight();
    int w = 50;
    int x = wW / 2 - w;


    getEntityManager().addEntity(new bmSpriteEntity("textures/biemlogo.png", x, 100, { 255, 255, 255, 255 }, -1, -1));


    bmScoreUIFactory sf;
    for(auto e : sf.sceneStart(wW, wH)) {
        getEntityManager().addEntity(e);
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
