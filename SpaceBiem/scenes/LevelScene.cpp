#include "stdafx.h"
#include "LevelScene.h"

#include "..\UniverseBuilder.h"

#include "..\entities\PlayerEntity.h"
#include "..\entities\PlanetEarthEntity.h"
#include "..\entities\PlanetMoonEntity.h"
#include "..\entities\ScoreUIEntity.h"
#include "..\entities\OxygenUIEntity.h"
#include "..\entities\ResourceUIEntity.h"
#include "..\factories\ScoreUIFactory.h"
#include "..\factories\PlanetFactory.h"

#include "MenuScene.h"
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

        getTransitionManager().getAudioDevice().playMusic("audio/spacemusic1.mp3", -1);
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
        getTransitionManager().drawBackground("textures/space.png");
        updateEntities(deltaTime);
        getTransitionManager().drawOverlay(Fonts::Roboto());
    }
}
