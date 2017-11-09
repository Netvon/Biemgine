#include "stdafx.h"
#include "bmLevelScene.h"

#include "..\entities\bmPlayerEntity.h"
#include "..\entities\bmPlanetEarthEntity.h"
#include "..\entities\bmPlanetMoonEntity.h"
#include "..\entities\bmScoreUIEntity.h"
#include "..\entities\bmOxygenUIEntity.h"
#include "..\factories\bmScoreUIFactory.h"

#include "bmMenuScene.h"
#include "..\systems\bmGravitySystem.h"
#include "..\systems\bmMovementSystem.h"
#include "..\systems\bmJumpSystem.h"
#include "..\systems\bmOxygenSystem.h"
#include "..\systems\bmOxygenUISystem.h"
#include "..\systems\bmScoreUISystem.h"
#include "..\systems\bmScoreSystem.h"

void bmLevelScene::created()
{
    enableRendering();
    enablePhysics();

    addSystem<bmGravitySystem>();
    addSystem<bmMovementSystem>();
    addSystem<bmJumpSystem>();
    addSystem<bmOxygenSystem>();
    addSystem<bmOxygenUISystem>();
    addSystem<bmScoreSystem>();
    addSystem<bmScoreUISystem>();

    float width = 15 * 2;
    float height = 25 * 2;

    addEntity(new bmPlayerEntity(800, 500, { 255, 255, 255, 255 }, width, height));

    int wW = getTransitionManager().getWindowWidth();
    int wH = getTransitionManager().getWindowHeight();
    int xMarge = 60;
    float p_size = (wW / 4) - (xMarge / 2);
    int yMarge = (wH - (p_size * 2)) / 2;

    addEntity(new bmOxygenUIEntity());
    addEntity(new bmScoreUIEntity());

    addEntity(new bmPlanetEarthEntity(xMarge + (p_size / 2), yMarge + (p_size / 2), { 255, 255, 255, 255 }, p_size, p_size));
    addEntity(new bmPlanetMoonEntity(xMarge + (p_size / 2) + (p_size * 2), yMarge + (p_size / 2), { 255, 255, 255, 255 }, p_size, p_size));

}

void bmLevelScene::sceneEnd() {

    bmScoreUIFactory sf;
    sf.sceneEnd(getEntities());

}


void bmLevelScene::input()
{
    if (im.isKeyDown("Q")) {
        signalQuit();
    }

    if (im.isKeyDown("Escape")) {
        getTransitionManager().navigateTo<bmMenuScene>();
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
