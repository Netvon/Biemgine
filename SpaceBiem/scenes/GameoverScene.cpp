#include "stdafx.h"
#include "GameoverScene.h"
#include "HighScoreScene.h"
#include "MenuScene.h"

#include "..\entities\PlanetEarthEntity.h"
#include "..\entities\PlanetMoonEntity.h"
#include "..\entities\ButtonUIEntity.h"
#include "..\factories\ScoreUIFactory.h"
#include "..\systems\ScoreUISystem.h"

using biemgine::PositionComponent;
using biemgine::ColorComponent;
using biemgine::UIComponent;
using biemgine::TextComponent;

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

        Entity* titleEntity = new Entity();

        titleEntity->addComponent("position", new PositionComponent(x, 100));
        titleEntity->addComponent("color", new ColorComponent(66, 143, 244));
        titleEntity->addComponent("ui", new UIComponent);
        titleEntity->addComponent("text", new TextComponent("Game over"));

        addEntity(titleEntity);


        addEntity(new PlanetEarthEntity(static_cast<float>(-100), static_cast<float>(wH - 200), { 255, 255, 255, 255 }, planetWidth, planetHeight, static_cast<float>(10)));
        addEntity(new PlanetMoonEntity(static_cast<float>(wW - 250), static_cast<float>(wH - 250), { 255, 255, 255, 255 }, planetWidth, planetHeight));

        addEntity(new ButtonUIEntity(x - 25, 600, { 255, 255, 255 }, 150, 50, "Highscores", GameoverHighscoreButtonClicked));
        addEntity(new ButtonUIEntity(x - 25, 675, { 255, 255, 255 }, 150, 50, "Menu", MenuButtonClicked));
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
