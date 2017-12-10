#include "stdafx.h"
#include "LevelScene.h"

#include "..\factories\UniverseBuilder.h"
#include "..\factories\UniverseGenerator.h"

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

#include "..\globals\Fonts.h"

#include <functional>
#include "..\factories\SaveBlobFactory.h"

using biemgine::TextComponent;
using biemgine::TextEntity;
using biemgine::TextUIEntity;
using biemgine::ScriptComponent;
using std::function;

namespace spacebiem
{
    void hover(StateManager* e)
    {
        e->getAudioDevice().playSoundEffect("audio/buttonhover.mp3", 0, -1, 128);
    }
    void resumeButtonClicked(StateManager* e) {
        cout << "Resume" << endl;
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

        enableCamera();
       
        enableRendering();
        enablePhysics();
        enableUI();
        enableScripts();

        addSystem<GravitySystem>();
        addSystem<MovementSystem>();
        addSystem<JumpSystem>();
        addSystem<OxygenSystem>();
        addSystem<OxygenUISystem>(2);
        addSystem<ScoreSystem>();
        addSystem<ScoreUISystem>(2);
        addSystem<ResourceUISystem>(2);
        addSystem<ResourceCollectingSystem>(2);
        addSystem<GameoverSystem>(2);

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
        timeout = 0;
        FPSId = addEntity<TextUIEntity>(Fonts::Roboto(), getTransitionManager().getWindowWidth() - 100, 0, Color{ 66, 143, 244 }, "");
        fpsEntity = getEntity(FPSId);
 
        int wW = getTransitionManager().getWindowWidth();
        int wH = getTransitionManager().getWindowHeight();

        UniverseBuilder uB;
        if (newGame) {

            UniverseGenerator uG;
            uG.generate(difficulty);


            uB.build(getEntityManager(), true);
        }
        else {
            uB.build(getEntityManager(), false);
        }

        int beginY = 400;
        int bW = 200;
        int bH = 60;
        int incr = bH + 15;
        
        addEntity<SpriteEntity>("textures/rectangle.png", 0.f, 0.f, Color{ 0, 0, 0, 60}, wW, wH, 300u, "pause_menu");
        addEntity<SpriteEntity>("textures/pause.png", (wW / 2) - (bW / 2) - 50, 325, Color{ 230, 230, 230 }, 300, 330, 290u, "pause_menu");
        addEntity<ButtonUIEntity>((wW / 2) - (bW / 2), beginY + (incr * 0), Color{ 35, 65, 112 }, Color::White(), Size{ bW,bH }, "Resume game", "textures/button_white.png", resumeButtonClicked, hover, "pause_menu");
        addEntity<ButtonUIEntity>((wW / 2) - (bW / 2), beginY + (incr * 1), Color{ 35, 65, 112 }, Color::White(), Size{ bW,bH }, "Help", "textures/button_white.png", helpButtonClicked, hover, "pause_menu");
        addEntity<ButtonUIEntity>((wW / 2) - (bW / 2), beginY + (incr * 2), Color{ 35, 65, 112 }, Color::White(), Size{ bW,bH }, "Return to menu", "textures/button_white.png", menuButtonClicked, hover, "pause_menu");

        updateMenu();

        getTransitionManager().getAudioDevice().playMusic("audio/spacemusic1.mp3", -1);
    }

    void LevelScene::sceneEnd() {
        saveScore();
    }

    void LevelScene::saveScore()
    {
        ScoreUIFactory sf;
        sf.sceneEnd(getEntityManager());
    }

    void LevelScene::saveGame()
    {
        SaveBlobFactory saveBlobFactory;
        vector<string> saveBlob = saveBlobFactory.createFromEntities(getEntityManager());

        FileHandler fileHandler("data/savegame.csv", true);

        for (auto it = saveBlob.begin(); it != saveBlob.end(); it++) {
            fileHandler.writeLine(*it);
        }
    }

    void LevelScene::input()
    {
        if (im.isKeyDown("Q")) {
            saveGame();
            signalQuit();
        }

        if (im.isKeyDown("Escape")) {
            saveGame();
            getTransitionManager().navigateTo<MenuScene>();
        }

        if (im.isKeyDown("F")) {
            //auto fpsEntity = getEntity(FPSId);
            auto fpsText = fpsEntity->getComponent<TextComponent>("text");

            if (fpsText->isVisible()) {
                fpsText->setVisible(false);
            }
            else {
                fpsText->setVisible(true);
            }
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

    void LevelScene::resetFPScounters()
    {
        timeout = 0;
        counter = 0;
        totalDeltaTime = 0;
    }

    void LevelScene::render(const float deltaTime)
    {
        //cout << static_cast<int>(1.f / (deltaTime / 1000.f)) << endl;
        totalDeltaTime += static_cast<int>(1.f / (deltaTime / 1000.f));
        counter++;
        if (timeout >= 500.f) {
            auto tc = getEntity(FPSId)->getComponent<TextComponent>("text");
            tc->setText("FPS: " + std::to_string(totalDeltaTime / counter), Color{ 255, 255, 255 });
            resetFPScounters();
        }

        timeout += deltaTime;

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
