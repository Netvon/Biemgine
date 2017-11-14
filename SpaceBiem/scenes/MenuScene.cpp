#include "MenuScene.h"

#include "..\factories\ScoreUIFactory.h"
#include "LevelScene.h"
#include "HighScoreScene.h"
#include "..\entities\PlanetEarthEntity.h"
#include "..\entities\PlanetMoonEntity.h"
#include "..\systems\ScoreUISystem.h"

using biemgine::SpriteEntity;

namespace spacebiem
{
    void MenuScene::created()
    {
        enableRendering();

        int wW = getTransitionManager().getWindowWidth();
        int wH = getTransitionManager().getWindowHeight();
        float planetWidth = 500;
        float planetHeight = 500;
        int w = 50;
        int x = wW / 2 - w;

        addEntity(new SpriteEntity("textures/biemlogo.png", x, 100, { 255, 255, 255, 255 }, -1, -1));
        addEntity(new PlanetEarthEntity(static_cast<float>(- 100), static_cast<float>(wH - 200), { 255, 255, 255, 255 }, planetWidth, planetHeight, static_cast<float>(10)));
        addEntity(new PlanetMoonEntity(static_cast<float>(wW - 250), static_cast<float>(wH - 250), { 255, 255, 255, 255 }, planetWidth, planetHeight));
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
