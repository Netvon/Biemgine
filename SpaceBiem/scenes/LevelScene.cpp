#include "stdafx.h"
#include "LevelScene.h"

#include "..\entities\PlayerEntity.h"
#include "..\entities\PlanetEarthEntity.h"
#include "..\entities\PlanetMoonEntity.h"
#include "..\entities\ScoreUIEntity.h"
#include "..\entities\OxygenUIEntity.h"
#include "..\factories\ScoreUIFactory.h"

#include "MenuScene.h"
#include "..\systems\GravitySystem.h"
#include "..\systems\MovementSystem.h"
#include "..\systems\JumpSystem.h"
#include "..\systems\OxygenSystem.h"
#include "..\systems\OxygenUISystem.h"
#include "..\systems\ScoreUISystem.h"
#include "..\systems\ScoreSystem.h"

namespace spacebiem
{
    void LevelScene::created()
    {
        enableRendering();
        enablePhysics();

        addSystem<GravitySystem>();
        addSystem<MovementSystem>();
        addSystem<JumpSystem>();
        addSystem<OxygenSystem>();
        addSystem<OxygenUISystem>();
        addSystem<ScoreSystem>();
        addSystem<ScoreUISystem>();

        float width = 15 * 2;
        float height = 25 * 2;

        addEntity(new PlayerEntity(800, 500, { 255, 255, 255, 255 }, width, height));

        int wW = getTransitionManager().getWindowWidth();
        int wH = getTransitionManager().getWindowHeight();
        int xMarge = 60;
        float p_size = (wW / 4) - (xMarge / 2);
        int yMarge = (wH - (p_size * 2)) / 2;

        addEntity(new OxygenUIEntity());
        addEntity(new ScoreUIEntity());

        addEntity(new PlanetEarthEntity(xMarge + (p_size / 2), yMarge + (p_size / 2), { 255, 255, 255, 255 }, p_size, p_size));
        addEntity(new PlanetMoonEntity(xMarge + (p_size / 2) + (p_size * 2), yMarge + (p_size / 2), { 255, 255, 255, 255 }, p_size, p_size));

    }

    void LevelScene::sceneEnd() {

        ScoreUIFactory sf;
        sf.sceneEnd(getEntities());
    }

    void LevelScene::input()
    {
        if (im.isKeyDown("Q")) {
            signalQuit();
        }

        if (im.isKeyDown("Escape")) {
            getTransitionManager().navigateTo<MenuScene>();
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

    void LevelScene::update()
    {
        if (!getTransitionManager().isPaused()) {
            updateEntities();
        }
    }

    void LevelScene::render(const float deltaTime)
    {
        getTransitionManager().drawBackground();
        updateEntities(deltaTime);
        getTransitionManager().drawOverlay();
    }
}
