#include "stdafx.h"
#include "bmMenuScene.h"
#include "bmSpriteEntity.h"
#include "bmScoreUIEntity.h"
#include "bmScoreUIFactory.h"


void bmMenuScene::sceneCreated()
{

    int wW = getTransitionManager().getWindowWidth();
    int wH = getTransitionManager().getWindowHeight();
    int w = 50;
    int x = wW / 2 - w;


    getEntityManager().addEntity(new bmSpriteEntity("textures/biemlogo.png", x, 100, { 255, 255, 255, 255 }, -1, -1));


    bmScoreUIFactory sf;
    for(auto e : sf.sceneStart(wW, wH)) {
        getEntityManager().addEntity(e);
    }
    
}


void bmMenuScene::input()
{
    if (im.isKeyDown("Q")) {
        signalQuit();
    }

    if (im.isKeyDown("Return")) {
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
