#include "MenuScene.h"

#include "..\factories\ScoreUIFactory.h"
#include "LevelScene.h"
#include "HighScoreScene.h"
#include "GameoverScene.h"
#include "..\entities\PlanetEarthEntity.h"
#include "..\entities\PlanetMoonEntity.h"
#include "..\entities\ButtonUIEntity.h"
#include "..\systems\ScoreUISystem.h"

using biemgine::SpriteEntity;
using biemgine::Size;

namespace spacebiem
{
    void PlayButtonClicked(StateManager* e)
    {
        e->navigateTo<LevelScene>();
    }

    void HighscoreButtonClicked(StateManager* e)
    {
        e->navigateTo<HighScoreScene>();
    }

    void GameOverButtonClicked(StateManager* e)
    {
        e->navigateTo<GameoverScene>();
    }

    void MenuScene::created()
    {
        enableRendering();
        enableUI();

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
        addEntity<PlanetEarthEntity>(-100.f, static_cast<float>(wH - 200), Color::White(), planetWidth, planetHeight, 0, 10.f);
        addEntity<PlanetMoonEntity>(static_cast<float>(wW - 250), static_cast<float>(wH - 250), Color::White(), planetWidth, planetHeight, 0);

        auto buttonTexture = "textures/button_white.png";
        auto buttonColor = Color{ 35, 65, 112 };
        auto buttonTextColor = Color::White();
        auto buttonSize = Size{ 150, 50 };

        addEntity<ButtonUIEntity>(x + 100, 300, buttonColor, buttonTextColor, buttonSize, "Play", buttonTexture, PlayButtonClicked);
        addEntity<ButtonUIEntity>(x + 100, 375, buttonColor, buttonTextColor, buttonSize, "Highscores", buttonTexture, HighscoreButtonClicked);
        addEntity<ButtonUIEntity>(x + 100, 450, buttonColor, buttonTextColor, buttonSize, "Quit", buttonTexture, [this](auto b) { signalQuit(); });
        addEntity<ButtonUIEntity>(x + 100, 525, buttonColor, buttonTextColor, buttonSize, "GameOverTest", buttonTexture, GameOverButtonClicked);
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
        getTransitionManager().drawBackground();
        updateEntities(deltaTime);
    }
}
