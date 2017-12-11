#include "stdafx.h"
#include "GameoverScene.h"
#include "HighScoreScene.h"
#include "MenuScene.h"

#include "..\entities\PlanetEarthEntity.h"
#include "..\entities\PlanetMoonEntity.h"
#include "..\entities\PlanetSandEntity.h"
#include "..\entities\PlanetToxicEntity.h"
#include "..\entities\PlanetIceEntity.h"
#include "..\entities\ButtonUIEntity.h"
#include "..\factories\ScoreUIFactory.h"
#include "..\entities\ScoreUIEntity.h"
#include "..\systems\ScoreUISystem.h"

#include "..\globals\Fonts.h"
#include "..\globals\Colors.h"

using biemgine::TextUIEntity;
using biemgine::SpriteEntity;

namespace spacebiem
{
    void onGameOverButtonEntered(StateManager* e)
    {
        e->getAudioDevice().playSoundEffect("audio/buttonhover.mp3", 0, -1, 128);
    }

    void MenuButtonClicked(StateManager* e)
    {
        e->getAudioDevice().playSoundEffect("audio/buttonclick.mp3", 0, -1, 128);
        e->getAudioDevice().playMusic("audio/menu.mp3", -1);
        e->navigateTo<MenuScene>();   
    }

    void GameoverScene::created()
    {
        enableRendering();
        enableUI();
        enableScripts();

        FileParser parser;
        parser.writeNewResources(resources);

        int wW = getTransitionManager().getWindowWidth();
        int wH = getTransitionManager().getWindowHeight();
        float planetWidth = 500;
        float planetHeight = 500;
        int w = 50;
        int x = wW / 2 - w;
        float resourcesX = x - 150.f;
        float planetsX = x + 150.f;

        /*planetsScore["sand"] = 3;
        planetsScore["earth"] = 5;
        planetsScore["toxic"] = 7;
        planetsScore["moon"] = 1;*/

        auto gameoverTexture = "textures/game_over.png";

        addEntity<SpriteEntity>(gameoverTexture, static_cast<float>(x - 50.f), 100.f, Color::White(), -1, -1, 100u);
        addEntity<TextUIEntity>(Fonts::Roboto(), resourcesX, 200.f, Color{ 66, 143, 244 }, "Resources");
        addEntity<TextUIEntity>(Fonts::Roboto(), planetsX, 200.f, Color{ 66, 143, 244 }, "Planets");

        float heightCounter = 250;

        for (auto& r : resources) {
            addEntity<SpriteEntity>("textures/" + r.first + ".png", resourcesX, heightCounter, Color::White(), 40, 40, 100u);
            addEntity<TextUIEntity>(Fonts::Roboto(), resourcesX + 45, heightCounter + 20, Color{ 66, 143, 244 }, " x " + std::to_string(r.second));
            heightCounter = heightCounter + 85.f;
        }

        heightCounter = 250;

        for (auto& p : planetsScore) {
            if (p.first == "earth") {
                addEntity<PlanetEarthEntity>(planetsX, heightCounter, Color{ 71, 166, 245, 255 }, 40, 40, 0, 10.f);
                addEntity<TextUIEntity>(Fonts::Roboto(), planetsX + 60, heightCounter + 15, Color{ 66, 143, 244 }, " x " + std::to_string(p.second));
                heightCounter = heightCounter + 85.f;
            }
            else if (p.first == "moon") {
                addEntity<PlanetMoonEntity>(planetsX, heightCounter, Color::White(), 40, 40, 0);
                addEntity<TextUIEntity>(Fonts::Roboto(), planetsX + 60, heightCounter + 15, Color{ 66, 143, 244 }, " x " + std::to_string(p.second));
                heightCounter = heightCounter + 85.f;
            }
            else if (p.first == "sand") {
                addEntity<PlanetSandEntity>(planetsX, heightCounter, Color{ 213,207,105,255 }, 40, 40, 0, 10.f);
                addEntity<TextUIEntity>(Fonts::Roboto(), planetsX + 60, heightCounter + 15, Color{ 66, 143, 244 }, " x " + std::to_string(p.second));
                heightCounter = heightCounter + 85.f;
            }
            else if (p.first == "toxic") {
                addEntity<PlanetToxicEntity>(planetsX, heightCounter, Color{ 20, 221, 53, 255 }, 40, 40, 0, 10.f);
                addEntity<TextUIEntity>(Fonts::Roboto(), planetsX + 60, heightCounter + 15, Color{ 66, 143, 244 }, " x " + std::to_string(p.second));
                heightCounter = heightCounter + 85.f;
            }
            else if (p.first == "ice") {
                addEntity<PlanetIceEntity>(planetsX, heightCounter, Colors::IceAtmosphere(), 40, 40, 0, 10.f);
                addEntity<TextUIEntity>(Fonts::Roboto(), planetsX + 60, heightCounter + 15, Color{ 66, 143, 244 }, " x " + std::to_string(p.second));
                heightCounter = heightCounter + 85.f;
            }
            
            
        }


        addEntity<TextUIEntity>(Fonts::Roboto(), x - 25, 700, Color::White(), "Total score: " + std::to_string(score));


        addEntity<PlanetEarthEntity>(-250.f, static_cast<float>(wH - 250), Color({71, 166, 245, 255}), planetWidth, planetHeight, 0, 10.f);
        addEntity<PlanetMoonEntity>(static_cast<float>(wW - 250), static_cast<float>(wH - 250), Color::White(), planetWidth, planetHeight, 0);

        auto buttonTexture = "textures/button_white.png";
        auto buttonColor = Color{ 35, 65, 112 };
        auto buttonTextColor = Color::White();
        auto buttonSize = Size{ 150, 50 };

        addEntity<ButtonUIEntity>(x - 25, 800, buttonColor, buttonTextColor, buttonSize, "Highscores", buttonTexture,
        [this](StateManager* manager)
        {
            /*ScoreUIFactory sf;
            sf.sceneEnd(getEntities());*/
            manager->getAudioDevice().playSoundEffect("audio/buttonclick.mp3", 0, -1, 128);
            manager->getAudioDevice().playMusic("audio/menu.mp3", -1);
            manager->navigateTo<HighScoreScene>(score);

        }, onGameOverButtonEntered);
        addEntity<ButtonUIEntity>(x - 25, 875, buttonColor, buttonTextColor, buttonSize, "Menu", buttonTexture, MenuButtonClicked, onGameOverButtonEntered);

        getTransitionManager().getAudioDevice().playMusic("audio/gameover.mp3", 0);
    }

    void GameoverScene::input()
    {
        if (im.isKeyDown("Q")) {
            signalQuit();
        }

        if (im.isKeyDown("Backspace")) {
            getTransitionManager().navigateTo<MenuScene>();
        }
    }

    void GameoverScene::update()
    {
        updateEntities();
    }

    void GameoverScene::render(const float deltaTime)
    {
        getTransitionManager().drawBackground("textures/space.png");
        updateEntities(deltaTime);
    }
}
