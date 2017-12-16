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
#include "..\systems\AIMovementSystem.h"

#include "..\globals\Fonts.h"

#include <functional>
#include <chrono>
#include "..\factories\SaveBlobFactory.h"
#include "..\globals\Functions.h"

using biemgine::TextComponent;
using biemgine::TextEntity;
using biemgine::TextUIEntity;
using biemgine::ScriptComponent;
using std::function;

namespace spacebiem
{

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
        addSystem<OxygenUISystem>();
        addSystem<ScoreSystem>();
        addSystem<ScoreUISystem>();
        addSystem<ResourceUISystem>();
        addSystem<ResourceCollectingSystem>();
        //addSystem<AIMovementSystem>();
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

        timeout = 0;
        FPSId = addEntity<TextUIEntity>(Fonts::Consolas(), getTransitionManager().getWindowWidth() - 220, 40, Color{ 66, 143, 244 }, "");
        speedId = addEntity<TextUIEntity>(Fonts::Consolas(), getTransitionManager().getWindowWidth() - 220, 10, Color{ 66, 143, 244 }, "");

        fpsEntity = getEntity(FPSId);
        speedEntity = getEntity(speedId);
 
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
        
        addEntity<SpriteEntity>("textures/rectangle.png", 0.f, 0.f, Color{0,0,0,60}, wW, wH, 280u, "pause_menu");
        addEntity<SpriteEntity>("textures/pause.png", (wW / 2) - (bW / 2) - 50, 325, Color{ 230, 230, 230, 255 }, 300, 330, 290u, "pause_menu");

        addEntity<ButtonUIEntity>((wW / 2) - (bW / 2), beginY + (incr * 0), Color{ 35, 65, 112 }, Color::White(), Size{ bW,bH }, "Resume game", "textures/button_white.png",
            [&](StateManager* e) {
            isPaused = false;
            updateMenu();
        }, nullptr, "pause_menu");

        addEntity<ButtonUIEntity>((wW / 2) - (bW / 2), beginY + (incr * 1), Color{ 35, 65, 112 }, Color::White(), Size{ bW,bH }, "Help", "textures/button_white.png",
            [this](StateManager* e) {
            saveGame();
            e->navigateTo<HelpScene>(true);
        }, nullptr, "pause_menu");

        addEntity<ButtonUIEntity>((wW / 2) - (bW / 2), beginY + (incr * 2), Color{ 35, 65, 112 }, Color::White(), Size{ bW,bH }, "Return to menu", "textures/button_white.png",
            [this](StateManager* e) {
            saveGame();
            e->navigateTo<MenuScene>();
        }, nullptr, "pause_menu");

        updateMenu();

        getTransitionManager().getAudioDevice().playMusic("audio/spacemusic1.mp3", -1);
    }

    void LevelScene::sceneEnd() {
        saveScore();
    }

    void LevelScene::close()
    {
        saveGame();
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
            auto speedText = speedEntity->getComponent<TextComponent>("text");

            if (fpsText->isVisible()) {
                fpsText->setVisible(false);
                speedText->setVisible(false);
            }
            else {
                fpsText->setVisible(true);
                speedText->setVisible(true);
            }
        }

        if (im.isKeyDown("Home")) {
            if (!isHomeButtonDown) {
                setFPSModifier(0);
                isHomeButtonDown = true;
            }
        }
        else {
            isHomeButtonDown = false;
        }

        if (im.isKeyDown("PageDown")) {
            if (!isPageDownButtonDown) {
                if (getFPSModifier() > -1) {
                    setFPSModifier(getFPSModifier() - 1);
                }
            }
            isPageDownButtonDown = true;
        }
        else {
            isPageDownButtonDown = false;
        }

        if (im.isKeyDown("PageUp")) {
            if (!isPageUpButtonDown) {
                if (getFPSModifier() < 1) {
                    setFPSModifier(getFPSModifier() + 1);
                }

                isPageUpButtonDown = true;
            }  
        }
        else {
            isPageUpButtonDown = false;
        }

        if (im.isKeyDown("P")) {
            if (!isPauseButtonDown) {

                isPaused = !isPaused;

                updateMenu();

                isPauseButtonDown = true;
            }
        }
        else {
            isPauseButtonDown = false;
        }
    }

    void LevelScene::update()
    {
        if (!isPaused) {
            //auto start = std::chrono::high_resolution_clock::now();

            updateEntities();

            //auto end = std::chrono::high_resolution_clock::now();
            //std::chrono::duration<double> diff = end - start;

            //std::cout << std::fixed;
            //std::cout << "time: " << diff.count() << std::endl;
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
        auto tc = speedEntity->getComponent<TextComponent>("text");
        tc->setText("Playback speed: " + std::to_string(getFPSModifier()) + "x", Color{ 255, 255, 255 });

        totalDeltaTime += deltaTime;
        counter++;
       
        if (timeout >= 500.f) {
            auto tc = fpsEntity->getComponent<TextComponent>("text");

            
            tc->setText("FPS: " + std::to_string(static_cast<int>(counter / totalDeltaTime * 1000)), Color{ 255, 255, 255 });
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
