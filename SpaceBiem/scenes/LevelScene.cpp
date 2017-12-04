#include "stdafx.h"
#include "LevelScene.h"

#include "..\UniverseBuilder.h"

#include "..\entities\PlayerEntity.h"
#include "..\entities\PlanetEarthEntity.h"
#include "..\entities\PlanetMoonEntity.h"
#include "..\entities\ScoreUIEntity.h"
#include "..\entities\OxygenUIEntity.h"
#include "..\entities\ResourceUIEntity.h"
#include "..\entities\ButtonUIEntity.h"
#include "..\factories\ScoreUIFactory.h"
#include "..\factories\PlanetFactory.h"

#include "MenuScene.h"
#include "HelpScene.h"
#include "..\systems\CameraSystem.h"
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
#include "..\systems\SaveBlobSystem.h"

#include "..\globals\Fonts.h"

#include <functional>

using biemgine::TextComponent;
using biemgine::TextEntity;
using biemgine::ScriptComponent;
using std::function;

namespace spacebiem
{

    void resumeButtonClicked(StateManager* e) {
        e->resumeGame();
    }
    void helpButtonClicked(StateManager* e) {
        e->navigateTo<HelpScene>(true);
    }
    void menuButtonClicked(StateManager* e) {
        e->resumeGame();
        e->navigateTo<MenuScene>();
    }

    void LevelScene::created()
    {
        addSystem<SaveBlobSystem>();
        addSystem<CameraSystem>();
       
        enableRendering();
        enablePhysics();
        enableUI();
        enableScripts();

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
                 
        addEntity<OxygenUIEntity>();
        addEntity<ScoreUIEntity>(25.f, 280.f);
        addEntity<SpriteEntity>("textures/resources-hud.png", 25.f, 25.f, Color::White(), 401.f, 169.f, 100u);
        addEntity<ResourceUIEntity>(66.f, 145.f, Color::White(), "uranium");
        addEntity<ResourceUIEntity>(157.f, 145.f, Color::White(), "diamond");
        addEntity<ResourceUIEntity>(248.f, 145.f, Color::White(), "metal");
        addEntity<ResourceUIEntity>(339.f, 145.f, Color::White(), "anti-matter");

        /*addEntity<TextEntity>("", Vector{ 1000.f, 100.f }, true, Color::White(), [this, playerId]()
        {
            auto player = getEntity(playerId)->getComponent<PhysicsComponent*>("physics");
            auto velo = player->getVelocity();

            return to_string(velo.x) + ":" + to_string(velo.y) + " ( " + to_string(velo.length()) + " )";
        });*/
 
        int wW = getTransitionManager().getWindowWidth();
        int wH = getTransitionManager().getWindowHeight();

        UniverseBuilder uB;
        if (newGame) {
            uB.build(getEntityManager(), true);
        }
        else {
            uB.build(getEntityManager(), false);
        }


        int beginY = 400;
        int bW = 200;
        int bH = 60;
        int incr = bH + 15;
        
        addEntity<SpriteEntity>("textures/rectangle.png", 0.f, 0.f, Color{0,0,0,60}, wW, wH, 300u, "pause_menu");
        addEntity<ButtonUIEntity>((wW / 2) - (bW / 2), beginY + (incr * 0), Color{ 35, 65, 112 }, Color::White(), Size{ bW,bH }, "Resume game", "textures/button_white.png", resumeButtonClicked, "pause_menu");
        addEntity<ButtonUIEntity>((wW / 2) - (bW / 2), beginY + (incr * 1), Color{ 35, 65, 112 }, Color::White(), Size{ bW,bH }, "Help", "textures/button_white.png", helpButtonClicked, "pause_menu");
        addEntity<ButtonUIEntity>((wW / 2) - (bW / 2), beginY + (incr * 2), Color{ 35, 65, 112 }, Color::White(), Size{ bW,bH }, "Return to menu", "textures/button_white.png", menuButtonClicked, "pause_menu");


        updateMenu();
    }

    void LevelScene::sceneEnd() {

        ScoreUIFactory sf;
        sf.sceneEnd(getEntityManager());
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

                if (isPaused) {
                    isPaused = false;
                    getTransitionManager().resumeGame();
                }
                else {
                    isPaused = true;
                    getTransitionManager().pauseGame();
                }

                updateMenu();

                isPauseButtonDown = true;
            }
        }
        else {
            isPauseButtonDown = false;
        }

        if (getTransitionManager().isPaused() != isPaused) {
            isPaused = getTransitionManager().isPaused();
            updateMenu();
        }
    }

    void LevelScene::update()
    {
        if (!isPaused) {
            updateEntities();
        }
    }

    void LevelScene::render(const float deltaTime)
    {
        getTransitionManager().drawBackground("textures/space.png");
        updateEntities(deltaTime);
    }


    void LevelScene::updateMenu()
    {
        auto em = getEntityManager();
        for (auto it = em->begin(); it != em->end(); it++) {

            if ((*it)->getTag() != "pause_menu") continue;

            if (isPaused) (*it)->rise();
            else (*it)->die();

        }

    }

}
