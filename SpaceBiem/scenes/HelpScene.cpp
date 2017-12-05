#include "stdafx.h"
#include "HelpScene.h"
#include "MenuScene.h"
#include "LevelScene.h"

#include "../entities/ButtonUIEntity.h"
#include "../entities/PlanetEarthEntity.h"
#include "../entities/PlayerEntity.h"

#include "../systems/MovementSystem.h"
#include "../systems/GravitySystem.h"

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
        enablePhysics();

        addSystem<GravitySystem>();
        addSystem<MovementSystem>();


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


        int pRadius = 300;
        switch (currentSlide){
        case 1:
            // slide 1 movement right/left
            addEntity<PlanetEarthEntity>((wW - pRadius) / 4 * 3, (wH - pRadius) / 2, Color::EarthAtmosphere(), pRadius, pRadius, 0, 0.f);
            addEntity<PlayerEntity>((wW - pRadius) / 4 * 3, (wH - pRadius) / 4, Color::White(), 25.f, 50.f, 1.0f);
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;
        case 7:
            break;
        case 8:
            break;
        case 9:
            break;
        default:
            break;
        }
        

        // slide 2 jump


        // slide 3 UI


        // slide 4 earth
        // slide 5 moon
        // slide 6 sand
        // slide 7 toxic
        // slide 8 ice
        // slide 9 lava


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

    void HelpScene::updateSlide()
    {
        
    }

}
