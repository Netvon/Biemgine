#include "MenuScene.h"

#include "..\factories\ScoreUIFactory.h"
#include "LevelScene.h"
#include "HighScoreScene.h"
#include "GameoverScene.h"
#include "HelpScene.h"
#include "CreditsScene.h"
#include "DifficultyScene.h"
#include "..\entities\PlanetEarthEntity.h"
#include "..\entities\PlanetMoonEntity.h"
#include "..\entities\ButtonUIEntity.h"
#include "..\systems\ScoreUISystem.h"
#include "..\systems\ResourceUISystem.h"
#include "..\entities\ResourceUIEntity.h"
#include "..\globals\Functions.h"

using biemgine::SpriteEntity;
using biemgine::Size;
using biemgine::FileHandler;

namespace spacebiem
{
    void MenuScene::created()
    {
        enableRendering();
        enableUI();
        enableScripts();

        getTransitionManager().getAudioDevice().stopSoundEffect("");

        addSystem<ResourceUISystem>();

        int wW = getTransitionManager().getWindowWidth();
        int wH = getTransitionManager().getWindowHeight();
        float planetWidth = 500;
        float planetHeight = 500;
        float playerWidth = 15 * 2;
        float playerHeight = 25 * 2;
        int w = 50;
        int x = wW / 2 - 175;

        addEntity<SpriteEntity>("textures/spacebiem.png", x, 100, Color::White(), -1, -1);
        addEntity<SpriteEntity>("textures/player-standing.png", x + 260, 115, Color::White(), playerWidth, playerHeight);
        addEntity<PlanetEarthEntity>(-250.f, static_cast<float>(wH - 250), Color({ 71, 166, 245, 255 }), planetWidth, planetHeight, 0, 10.f);
        addEntity<PlanetMoonEntity>(static_cast<float>(wW - 250), static_cast<float>(wH - 250), Color::White(), planetWidth, planetHeight, 0);

        auto buttonTexture = "textures/button_white.png";
        auto buttonColor = Color{ 35, 65, 112 };
        auto buttonTextColor = Color::White();
        auto buttonSize = Size{ 150, 50 };

        int beginY = 330;
        int incr = 65;

        auto newGameClick = [](StateManager* e) { e->navigateTo<DifficultyScene>(); };
        auto continueClick = [](StateManager* e) { e->navigateTo<LevelScene>(false); };
        auto highscoreClick =[](StateManager* e) { e->navigateTo<HighScoreScene>(); };
        auto helpClick = [](StateManager* e) { e->navigateTo<HelpScene>(); };
        auto CreditsButtonClicked = [](StateManager* e) { e->navigateTo<CreditsScene>(); };

        addEntity<ButtonUIEntity>(x + 100, beginY + (incr * 0), buttonColor, buttonTextColor, buttonSize, "New game", buttonTexture, newGameClick, nullptr);

        std::function<void(StateManager*)> continueEventHandler = nullptr;
        bool saveBlobExists = FileHandler::exists("data/savegame.csv");

        if (saveBlobExists) {
            continueEventHandler = continueClick;
        }

        addEntity<ButtonUIEntity>(x + 100, beginY + (incr * 1), buttonColor, buttonTextColor, buttonSize, "Continue", buttonTexture, continueEventHandler, nullptr);
        
        beginY += 20;
        addEntity<ButtonUIEntity>(x + 100, beginY + (incr * 2), buttonColor, buttonTextColor, buttonSize, "Highscores", buttonTexture, highscoreClick, nullptr);
        addEntity<ButtonUIEntity>(x + 100, beginY + (incr * 3), buttonColor, buttonTextColor, buttonSize, "Upgrades", buttonTexture);
        addEntity<ButtonUIEntity>(x + 100, beginY + (incr * 4), buttonColor, buttonTextColor, buttonSize, "Help", buttonTexture, helpClick, nullptr);
        addEntity<ButtonUIEntity>(x + 100, beginY + (incr * 5), buttonColor, buttonTextColor, buttonSize, "Settings", buttonTexture);
        addEntity<ButtonUIEntity>(x + 100, beginY + (incr * 6), buttonColor, buttonTextColor, buttonSize, "Credits", buttonTexture, CreditsButtonClicked);
        beginY += 20;
        addEntity<ButtonUIEntity>(x + 100, beginY + (incr * 7), buttonColor, buttonTextColor, buttonSize, "Quit", buttonTexture, [this](auto b) { signalQuit(); }, nullptr);

        FileParser parser;
        map<string, int> resources = parser.resourcesContent();

        addEntity<SpriteEntity>("textures/resources-hud.png", 25.f, 25.f, Color::White(), 401, 169, 100u);
        float rX = 66.f;
        float rIncr = 91.f;
        addEntity<ResourceUIEntity>(rX + (rIncr * 0), 145.f, Color::White(), "uranium", resources["uranium"]);
        addEntity<ResourceUIEntity>(rX + (rIncr * 1), 145.f, Color::White(), "diamond", resources["diamond"]);
        addEntity<ResourceUIEntity>(rX + (rIncr * 2), 145.f, Color::White(), "metal", resources["metal"]);
        addEntity<ResourceUIEntity>(rX + (rIncr * 3), 145.f, Color::White(), "anti-matter", resources["anti-matter"]);

        if(!getTransitionManager().getAudioDevice().isPlayingMusic("audio/menu.mp3"))
            getTransitionManager().getAudioDevice().playMusic("audio/menu.mp3", -1);  
    }

    void MenuScene::input()
    {
        if (im.isKeyDown("Q")) {
            signalQuit();
        }

        if (im.isKeyDown("S")) {
            getTransitionManager().navigateTo<HighScoreScene>();
        }

        if (im.isKeyDown("Return")) {
            getTransitionManager().getAudioDevice().playSoundEffect("audio/switch.mp3", 0, 5, 64);
            getTransitionManager().navigateTo<LevelScene>();
        }
    }

    void MenuScene::update()
    {
        updateEntities();
    }

    void MenuScene::render(const float deltaTime)
    {
        getTransitionManager().drawBackground("textures/space.png");
        updateEntities(deltaTime);
    }
}
