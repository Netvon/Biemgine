#include "MenuScene.h"

#include "..\factories\ScoreUIFactory.h"
#include "LevelScene.h"
#include "HighScoreScene.h"
#include "..\entities\PlanetEarthEntity.h"
#include "..\entities\PlanetMoonEntity.h"
#include "..\entities\ButtonUIEntity.h"
#include "..\systems\ScoreUISystem.h"

using biemgine::SpriteEntity;

namespace spacebiem
{
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

        addEntity(new SpriteEntity("textures/teambiem.png", x, 100, { 255, 255, 255, 255 }, -1, -1));
        addEntity(new SpriteEntity("textures/player-standing.png", x + 260, 115, { 255, 255, 255, 255 }, playerWidth, playerHeight));
        addEntity(new PlanetEarthEntity(static_cast<float>(- 100), static_cast<float>(wH - 200), { 255, 255, 255, 255 }, planetWidth, planetHeight, static_cast<float>(10)));
        addEntity(new PlanetMoonEntity(static_cast<float>(wW - 250), static_cast<float>(wH - 250), { 255, 255, 255, 255 }, planetWidth, planetHeight));

        addEntity(new ButtonUIEntity(x + 100, 300, { 0, 0, 0, 0 }, 150, 50, "Play"));
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
