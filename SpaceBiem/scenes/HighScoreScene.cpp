#include "stdafx.h"
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
using biemgine::Size;

namespace spacebiem
{
    void BackButtonClicked(StateManager* e)
    {
        e->navigateTo<MenuScene>();
    }

    void HighScoreScene::created() {
        enableRendering();
        enableUI();

        addSystem<ScoreUISystem>();

        int wW = getTransitionManager().getWindowWidth();
        int wH = getTransitionManager().getWindowHeight();
        float planetWidth = 500;
        float planetHeight = 500;
        int w = 50;
        int x = wW / 2 - w;

        auto titleEntityId = addEntity<Entity>();
        auto titleEntity = getEntityManager()->getEntity(titleEntityId);

        titleEntity->addComponent<PositionComponent>("position", x, 100);
        titleEntity->addComponent<ColorComponent>("color", 66, 143, 244);
        titleEntity->addComponent<UIComponent>("ui");
        titleEntity->addComponent<TextComponent>("text", "Highscores");

        //addEntity(titleEntity);

        ScoreUIFactory sf;
        for (auto e : sf.sceneStart(wW, wH)) {
            addEntity(e);
        }

        addEntity<PlanetEarthEntity>(static_cast<float>(-100), static_cast<float>(wH - 200), Color({ 71, 166, 245, 255 }), planetWidth, planetHeight, 0, static_cast<float>(10));
        addEntity<PlanetMoonEntity>(static_cast<float>(wW - 250), static_cast<float>(wH - 250), Color::White(), planetWidth, planetHeight, 0);
        
        addEntity<ButtonUIEntity>(x, 750, Color{ 100, 50, 50 }, Color::White(), Size{ 150, 50 }, "Back", "textures/button_white.png", BackButtonClicked);
    }

    void HighScoreScene::input()
    {
        if (im.isKeyDown("Q")) {
            signalQuit();
        }

        if (im.isKeyDown("Backspace")) {
            getTransitionManager().navigateTo<MenuScene>();
        }
    }

    void HighScoreScene::update()
    {
        updateEntities();
    }

    void HighScoreScene::render(const float deltaTime)
    {
        getTransitionManager().drawBackground();
        updateEntities(deltaTime);
    }
}
