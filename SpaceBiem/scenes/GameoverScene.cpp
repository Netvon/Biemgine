#include "stdafx.h"
#include "GameoverScene.h"
#include "HighScoreScene.h"
#include "MenuScene.h"

#include "..\entities\PlanetEarthEntity.h"
#include "..\entities\PlanetMoonEntity.h"
#include "..\entities\ButtonUIEntity.h"
#include "..\factories\ScoreUIFactory.h"
#include "..\entities\ScoreUIEntity.h"
#include "..\systems\ScoreUISystem.h"

using biemgine::PositionComponent;
using biemgine::ColorComponent;
using biemgine::UIComponent;
using biemgine::TextComponent;
using biemgine::TextUIEntity;

namespace spacebiem
{
    void GameoverHighscoreButtonClicked(StateManager* e)
    {
        e->navigateTo<HighScoreScene>();
    }

    void MenuButtonClicked(StateManager* e)
    {
        e->navigateTo<MenuScene>();
    }

    void GameoverScene::created()
    {
        enableRendering();
        enableUI();

        int wW = getTransitionManager().getWindowWidth();
        int wH = getTransitionManager().getWindowHeight();
        float planetWidth = 500;
        float planetHeight = 500;
        int w = 50;
        int x = wW / 2 - w;

        addEntity<TextUIEntity>(static_cast<float>(x), 100.f, Color { 66, 143, 244 }, "Game over");
        addEntity<TextUIEntity>(static_cast<float>(x), 150.f, Color{ 66, 143, 244 }, "Je score was: " + std::to_string(score));

        addEntity<PlanetEarthEntity>(-100.f, static_cast<float>(wH - 200), Color::White(), planetWidth, planetHeight, 0, 10.f);
        addEntity<PlanetMoonEntity>(static_cast<float>(wW - 250), static_cast<float>(wH - 250), Color::White(), planetWidth, planetHeight, 0);

        auto buttonTexture = "textures/button_white.png";
        auto buttonColor = Color{ 35, 65, 112 };
        auto buttonTextColor = Color::White();
        auto buttonSize = Size{ 150, 50 };

        addEntity<ButtonUIEntity>(x - 25, 300, buttonColor, buttonTextColor, buttonSize, "Highscores", buttonTexture, GameoverHighscoreButtonClicked);
        addEntity<ButtonUIEntity>(x - 25, 375, buttonColor, buttonTextColor, buttonSize, "Menu", buttonTexture, MenuButtonClicked);
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
        getTransitionManager().drawBackground();
        updateEntities(deltaTime);
    }
}
