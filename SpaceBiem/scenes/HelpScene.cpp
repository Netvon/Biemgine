#include "stdafx.h"
#include "HelpScene.h"
#include "MenuScene.h"
#include "LevelScene.h"

#include "../entities/ButtonUIEntity.h"

#include "..\globals\Fonts.h"

using biemgine::TextUIEntity;
using biemgine::SpriteEntity;

namespace spacebiem
{

    void previousButtonClicked(StateManager* e)
    {

    }
    void nextButtonClicked(StateManager* e)
    {

    }
    void returnToGameButtonClicked(StateManager* e)
    {
        e->navigateTo<LevelScene>();
    }
    void returnToMenuButtonClicked(StateManager* e)
    {
        e->navigateTo<MenuScene>();
    }



    void HelpScene::created()
    {
        enableRendering();
        enableUI();
        enableScripts();


        int wW = getTransitionManager().getWindowWidth();
        int wH = getTransitionManager().getWindowHeight();
        int bW = 200;
        int bH = 50;
        int edgeMargin = 20;
        int middleMargin = 10;


        if (fromLevel) {
            addEntity<ButtonUIEntity>((wW - bW - bW) / 2 - middleMargin, wH - edgeMargin - bH, Color{ 35, 65, 112 }, Color::White(), Size{ bW,bH }, "Return to menu", "textures/button_white.png", returnToMenuButtonClicked);
            addEntity<ButtonUIEntity>((wW) / 2 + middleMargin, wH - edgeMargin - bH, Color{ 35, 65, 112 }, Color::White(), Size{ bW,bH }, "Return to game", "textures/button_white.png", returnToGameButtonClicked);
        }
        else {
            addEntity<ButtonUIEntity>((wW-bW)/2, wH - edgeMargin - bH, Color{ 35, 65, 112 }, Color::White(), Size{ bW,bH }, "Return to menu", "textures/button_white.png", returnToMenuButtonClicked);
        }

        addEntity<ButtonUIEntity>(edgeMargin, wH - edgeMargin - bH, Color{ 35, 65, 112 }, Color::White(), Size{ bW,bH }, "Previous", "textures/button_white.png", previousButtonClicked);
        addEntity<ButtonUIEntity>(wW-edgeMargin-bW, wH - edgeMargin - bH, Color{ 35, 65, 112 }, Color::White(), Size{ bW,bH }, "Next", "textures/button_white.png", nextButtonClicked);






    }

    void HelpScene::input()
    {
        if (im.isKeyDown("Q")) {
            signalQuit();
        }

        if (im.isKeyDown("Backspace")) {
            getTransitionManager().navigateTo<MenuScene>();
        }
    }

    void HelpScene::update()
    {
        updateEntities();
    }

    void HelpScene::render(const float deltaTime)
    {
        getTransitionManager().drawBackground("textures/space.png");
        updateEntities(deltaTime);
    }
}
