#include "stdafx.h"
#include "bmMenuScene.h"

#include "..\factories\bmScoreUIFactory.h"
#include "bmLevelScene.h"
#include "..\systems\bmScoreUISystem.h"

void bmMenuScene::sceneCreated()
{
    enableRendering();
    addSystem<bmScoreUISystem>();

    int wW = getTransitionManager().getWindowWidth();
    int wH = getTransitionManager().getWindowHeight();
    int w = 50;
    int x = wW / 2 - w;


    addEntity(new bmSpriteEntity("textures/biemlogo.png", x, 100, { 255, 255, 255, 255 }, -1, -1));


    bmScoreUIFactory sf;
    for(auto e : sf.sceneStart(wW, wH)) {
        addEntity(e);
    }
    
}


void bmMenuScene::input()
{
    if (im.isKeyDown("Q")) {
        signalQuit();
    }

    if (im.isKeyDown("Return")) {
        getTransitionManager().navigateTo<bmLevelScene>();
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
