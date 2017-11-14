#include "stdafx.h"
#include "LevelScene.h"

#include "..\entities\PlayerEntity.h"
#include "..\entities\PlanetEarthEntity.h"
#include "..\entities\PlanetMoonEntity.h"
#include "..\entities\ScoreUIEntity.h"
#include "..\entities\OxygenUIEntity.h"
#include "..\ResourceUIEntity.h"
#include "..\factories\ScoreUIFactory.h"
#include "..\factories\PlanetFactory.h"

#include "MenuScene.h"
#include "..\systems\GravitySystem.h"
#include "..\systems\MovementSystem.h"
#include "..\systems\JumpSystem.h"
#include "..\systems\OxygenSystem.h"
#include "..\systems\OxygenUISystem.h"
#include "..\systems\ScoreUISystem.h"
#include "..\systems\ScoreSystem.h"
#include "..\ResourceUISystem.h"

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
        addSystem<ResourceUISystem>();

        float width = 15 * 2;
        float height = 25 * 2;

        addEntity(new PlayerEntity(800, 500, { 255, 255, 255, 255 }, width, height));

        addEntity(new OxygenUIEntity());
        //addEntity(new ScoreUIEntity());
        addEntity(new SpriteEntity("textures/resources-hud.png", 25, 25, {255, 255, 255, 255}, 401, 169, 100u));
        addEntity(new ResourceUIEntity(66, 150, {255, 255, 255, 255}, "uranium"));
        addEntity(new ResourceUIEntity(157, 150, {255, 255, 255, 255}, "diamond"));
        addEntity(new ResourceUIEntity(248, 150, {255, 255, 255, 255}, "metal"));
        addEntity(new ResourceUIEntity(339, 150, {255, 255, 255, 255}, "anti-matter"));
 
        int wW = getTransitionManager().getWindowWidth();
        int wH = getTransitionManager().getWindowHeight();

        PlanetFactory pf;
        for (auto e : pf.sceneStart(wW, wH)) {
            addEntity(e);
        }
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
