#include "MenuScene.h"

#include "..\factories\ScoreUIFactory.h"
#include "LevelScene.h"
#include "HighScoreScene.h"
#include "..\entities\PlanetEarthEntity.h"
#include "..\entities\PlanetMoonEntity.h"
#include "..\entities\ButtonUIEntity.h"
#include "..\systems\ScoreUISystem.h"

using biemgine::SpriteEntity;
using biemgine::Size;

namespace spacebiem
{
    void newGameButtonClicked(StateManager* e)
    {
        e->navigateTo<LevelScene>(true);
    }

    void ContinueButtonClicked(StateManager* e)
    {
        e->navigateTo<LevelScene>(false);
    }

    void HighscoreButtonClicked(StateManager* e)
    {
        e->navigateTo<HighScoreScene>();
    }

    void MenuScene::created()
    {
        enableRendering();
        enableUI();
        enableScripts();

        int wW = getTransitionManager().getWindowWidth();
        int wH = getTransitionManager().getWindowHeight();
        float planetWidth = 500;
        float planetHeight = 500;
        float playerWidth = 15 * 2;
        float playerHeight = 25 * 2;
        int w = 50;
        int x = wW / 2 - 175;

        addEntity<SpriteEntity>("textures/teambiem.png", x, 100, Color::White(), -1, -1);

        addEntity<SpriteEntity>("textures/player-standing.png", x + 260, 115, Color::White(), playerWidth, playerHeight);
        addEntity<PlanetEarthEntity>(-100.f, static_cast<float>(wH - 200), Color({ 71, 166, 245, 255 }), planetWidth, planetHeight, 0, 10.f);
        addEntity<PlanetMoonEntity>(static_cast<float>(wW - 250), static_cast<float>(wH - 250), Color::White(), planetWidth, planetHeight, 0);

        auto buttonTexture = "textures/button_white.png";
        auto buttonColor = Color{ 100, 50, 50 };
        auto buttonTextColor = Color::White();
        auto buttonSize = Size{ 150, 50 };

        int beginY = 330;
        int incr = 65;

        addEntity<ButtonUIEntity>(x + 100, beginY + (incr * 0), buttonColor, buttonTextColor, buttonSize, "New game", buttonTexture, newGameButtonClicked);
        addEntity<ButtonUIEntity>(x + 100, beginY + (incr * 1), buttonColor, buttonTextColor, buttonSize, "Continue", buttonTexture, ContinueButtonClicked);
        beginY += 20;
        addEntity<ButtonUIEntity>(x + 100, beginY + (incr * 2), buttonColor, buttonTextColor, buttonSize, "Highscores", buttonTexture, HighscoreButtonClicked);
        addEntity<ButtonUIEntity>(x + 100, beginY + (incr * 3), buttonColor, buttonTextColor, buttonSize, "Upgrades", buttonTexture);
        addEntity<ButtonUIEntity>(x + 100, beginY + (incr * 4), buttonColor, buttonTextColor, buttonSize, "Tutorial", buttonTexture);
        addEntity<ButtonUIEntity>(x + 100, beginY + (incr * 5), buttonColor, buttonTextColor, buttonSize, "Settings", buttonTexture);
        addEntity<ButtonUIEntity>(x + 100, beginY + (incr * 6), buttonColor, buttonTextColor, buttonSize, "Credits", buttonTexture);
        beginY += 20;
        addEntity<ButtonUIEntity>(x + 100, beginY + (incr * 7), buttonColor, buttonTextColor, buttonSize, "Quit", buttonTexture, [this](auto b) { signalQuit(); });
        

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
