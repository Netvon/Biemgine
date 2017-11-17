#include "stdafx.h"
#include "LevelScene.h"

#include "..\entities\PlayerEntity.h"
#include "..\entities\PlanetEarthEntity.h"
#include "..\entities\PlanetMoonEntity.h"
#include "..\entities\ScoreUIEntity.h"
#include "..\entities\OxygenUIEntity.h"
#include "..\entities\ResourceUIEntity.h"
#include "..\factories\ScoreUIFactory.h"
#include "..\factories\PlanetFactory.h"

#include "..\systems\GravitySystem.h"
#include "..\systems\MovementSystem.h"
#include "..\systems\JumpSystem.h"
#include "..\systems\OxygenSystem.h"
#include "..\systems\OxygenUISystem.h"
#include "..\systems\ScoreUISystem.h"
#include "..\systems\ScoreSystem.h"
#include "..\systems\ResourceUISystem.h"
#include "..\systems\ResourceCollectingSystem.h"
#include "..\systems\GameoverSystem.h"

namespace spacebiem
{
    void LevelScene::created()
    {
        enableRendering();
        enablePhysics();
        enableUI();

        addSystem<GravitySystem>();
        addSystem<MovementSystem>();
        addSystem<JumpSystem>();
        addSystem<OxygenSystem>();
        addSystem<OxygenUISystem>();
        addSystem<ScoreSystem>();
        addSystem<ScoreUISystem>();
        addSystem<ResourceUISystem>();
        addSystem<ResourceCollectingSystem>();
        addSystem<GameoverSystem>();

        float width = 15 * 2;
        float height = 25 * 2;

        addEntity<PlayerEntity>(800, 500, Color::White(), width, height);
                 
        addEntity<OxygenUIEntity>();
        addEntity<ScoreUIEntity>();
        addEntity<SpriteEntity>("textures/resources-hud.png", 25, 25, Color::White(), 401, 169, 100u);
        addEntity<ResourceUIEntity>(66, 150, Color::White(), "uranium");
        addEntity<ResourceUIEntity>(157, 150, Color::White(), "diamond");
        addEntity<ResourceUIEntity>(248, 150, Color::White(), "metal");
        addEntity<ResourceUIEntity>(339, 150, Color::White(), "anti-matter");
 
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
        //getTransitionManager().navigateTo<GameoverScene>();
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
