#include "stdafx.h"

#include "DifficultyScene.h"
#include "MenuScene.h"
#include "LevelScene.h"

#include "..\entities\PlanetEarthEntity.h"
#include "..\entities\PlanetMoonEntity.h"

#include "..\entities\ButtonUIEntity.h"

#include "..\globals\Fonts.h"
#include "..\globals\Difficulty.h"

using biemgine::TextUIEntity;
using biemgine::SpriteEntity;

namespace spacebiem
{

    void DifficultyScene::created()
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
        int x = wW / 2 - w;

        addEntity<SpriteEntity>("textures/spacebiem.png", wW / 2 - 175, 100, Color::White(), -1, -1);
        addEntity<SpriteEntity>("textures/player-standing.png", wW / 2 - 175 + 260, 115, Color::White(), playerWidth, playerHeight);
        addEntity<PlanetEarthEntity>(-100.f, static_cast<float>(wH - 200), Color{ 71, 166, 245, 255 }, planetWidth, planetHeight, 0, 10.f);
        addEntity<PlanetMoonEntity>(static_cast<float>(wW - 250), static_cast<float>(wH - 250), Color::White(), planetWidth, planetHeight, 0);

        auto buttonTexture = "textures/button_white.png";
        auto buttonColor = Color{ 35, 65, 112 };
        auto buttonTextColor = Color::White();
        auto buttonSize = Size{ 150, 50 };

        int beginY = 380;
        int incr = 65;

        addEntity<ButtonUIEntity>(x - 25, beginY + (0 * incr), Color{ 22, 94, 22 }, buttonTextColor, buttonSize, "Normal", buttonTexture,
            [this](StateManager* manager)
        {
            manager->navigateTo<LevelScene>(true, Difficulty::NORMAL);
        });

        addEntity<ButtonUIEntity>(x - 25, beginY + (1 * incr), Color{ 188, 103, 0 }, buttonTextColor, buttonSize, "Challenging", buttonTexture,
            [this](StateManager* manager)
        {
            manager->navigateTo<LevelScene>(true, Difficulty::CHALLENING);
        });

        addEntity<ButtonUIEntity>(x - 25, beginY + (2 * incr), Color{ 135, 25, 25 }, buttonTextColor, buttonSize, "Expert", buttonTexture,
            [this](StateManager* manager)
        {
            manager->navigateTo<LevelScene>(true, Difficulty::EXPERT);
        });

        beginY += 20;
        addEntity<ButtonUIEntity>(x - 25, beginY + (3 * incr), buttonColor, buttonTextColor, buttonSize, "Menu", buttonTexture,
            [this](StateManager* manager)
        {
            manager->navigateTo<MenuScene>();
        });

    }

    void DifficultyScene::input()
    {
        if (im.isKeyDown("Q")) {
            signalQuit();
        }

        if (im.isKeyDown("Backspace")) {
            getTransitionManager().navigateTo<MenuScene>();
        }
    }

    void DifficultyScene::update()
    {
        updateEntities();
    }

    void DifficultyScene::render(const float deltaTime)
    {
        getTransitionManager().drawBackground("textures/space.png");
        updateEntities(deltaTime);
    }
}
