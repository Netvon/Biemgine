#include "stdafx.h"
#include "HelpScene.h"
#include "MenuScene.h"
#include "LevelScene.h"

#include "../entities/ButtonUIEntity.h"
#include "../entities/PlayerEntity.h"

#include "..\entities\ScoreUIEntity.h"
#include "..\entities\OxygenUIEntity.h"
#include "..\entities\ResourceUIEntity.h"

#include "../entities/PlanetEarthEntity.h"
#include "../entities/PlanetMoonEntity.h"
#include "../entities/PlanetSandEntity.h"
#include "../entities/PlanetToxicEntity.h"
#include "../entities/PlanetLavaEntity.h"
#include "../entities/PlanetIceEntity.h"

#include "../systems/MovementSystem.h"
#include "../systems/GravitySystem.h"
#include "../systems/JumpSystem.h"
#include "..\systems\OxygenSystem.h"
#include "..\systems\OxygenUISystem.h"
#include "..\systems\ScoreUISystem.h"
#include "..\systems\ScoreSystem.h"
#include "..\systems\ResourceUISystem.h"
#include "..\systems\ResourceCollectingSystem.h"

#include "..\globals\Fonts.h"
#include "..\globals\Colors.h"
#include "..\FileParser.h"

using biemgine::AnimationComponent;
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
        e->navigateTo<LevelScene>(false);
    }
    void returnToMenuButtonClicked(StateManager* e)
    {
        e->navigateTo<MenuScene>();
    }

    void HelpScene::created()
    {
        enableRendering();
        enablePhysics();
        enableUI();
        enableScripts();
        enableAnimations();

        addSystem<GravitySystem>();
        addSystem<MovementSystem>();
        addSystem<JumpSystem>();

        getTransitionManager().getAudioDevice().stopSoundEffect("");

        if (currentSlide > 1) {
            addSystem<OxygenSystem>();
            addSystem<OxygenUISystem>();
            addSystem<ScoreSystem>();
            addSystem<ScoreUISystem>();
            addSystem<ResourceUISystem>();
            addSystem<ResourceCollectingSystem>();
        }

        int wW = getTransitionManager().getWindowWidth();
        int wH = getTransitionManager().getWindowHeight();
        int bW = 200;
        int bH = 50;
        int edgeMargin = 20;
        int middleMargin = 10;


        int overlayId = addEntityExtra<SpriteEntity>([](Entity* entity)
        {
            entity->addComponent("animation", new AnimationComponent(255, 0, 300.f,[sprite = entity->getComponent<TextureComponent>("texture")](float newValue) { sprite->setColor(sprite->getColor().WithAlpha(newValue)); }, nullptr, false));
        }, "textures/rectangle.png", 0, 0, Color{ 0, 0, 0, 0 }, wW, wH, 9999);

        auto overlayEntity = getEntity(overlayId);
        auto overlayAnimation = overlayEntity->getComponent<AnimationComponent>("animation");
      
        if(fade)
            overlayAnimation->play();
        if (fromLevel) {
            addEntity<ButtonUIEntity>((wW - bW - bW) / 2 - middleMargin, wH - edgeMargin - bH, Color{ 35, 65, 112 }, Color::White(), Size{ bW,bH }, "Return to menu", "textures/button_white.png", returnToMenuButtonClicked);
            addEntity<ButtonUIEntity>((wW) / 2 + middleMargin, wH - edgeMargin - bH, Color{ 35, 65, 112 }, Color::White(), Size{ bW,bH }, "Return to game", "textures/button_white.png",
                                      [this, overlayAnimation](StateManager* e)
            { overlayAnimation->setOnFinished([e] { e->navigateTo<LevelScene>(false); }); overlayAnimation->playReversed(); });
        }
        else {
            addEntity<ButtonUIEntity>((wW-bW)/2, wH - edgeMargin - bH, Color{ 35, 65, 112 }, Color::White(), Size{ bW,bH }, "Return to menu", "textures/button_white.png", returnToMenuButtonClicked);
        }

        if(currentSlide > 1)addEntity<ButtonUIEntity>(edgeMargin, wH - edgeMargin - bH, Color{ 35, 65, 112 }, Color::White(), Size{ bW,bH }, "Previous", "textures/button_white.png", [this](StateManager* e) { e->navigateTo<HelpScene>(fromLevel, false, currentSlide - 1); });
        else addEntity<ButtonUIEntity>(edgeMargin, wH - edgeMargin - bH, Color{ 35, 65, 112 }, Color::White(), Size{ bW,bH }, "Previous", "textures/button_white.png");

        if(currentSlide < maxSlides) addEntity<ButtonUIEntity>(wW - edgeMargin - bW, wH - edgeMargin - bH, Color{ 35, 65, 112 }, Color::White(), Size{ bW,bH }, "Next", "textures/button_white.png", [this](StateManager* e) { e->navigateTo<HelpScene>(fromLevel, false, currentSlide + 1); });
        else addEntity<ButtonUIEntity>(wW - edgeMargin - bW, wH - edgeMargin - bH, Color{ 35, 65, 112 }, Color::White(), Size{ bW,bH }, "Next", "textures/button_white.png");


        int pRadius = 500;
        int planetX = (wW - (pRadius*1.5f));
        int planetY = (wH - pRadius) / 2;


        FileParser fp;
        auto atmosphere = fp.atmosphereContent();
        auto score = fp.planetScoreContent();

        // Planet in the slide
        if (currentSlide > 1 && currentSlide <= 4) addEntity<PlanetEarthEntity>(planetX, planetY, Colors::EarthAtmosphere(), pRadius, pRadius, score["earth"], atmosphere["earth"], "Type: Earth");
        else if (currentSlide == 5) addEntity<PlanetMoonEntity>(planetX, planetY, Colors::MoonAtmosphere(), pRadius, pRadius, score["moon"], "Type: Moon");
        else if (currentSlide == 6) addEntity<PlanetSandEntity>(planetX, planetY, Colors::SandAtmosphere(), pRadius, pRadius, score["sand"], atmosphere["sand"], "Type: Sand");
        else if (currentSlide == 7) addEntity<PlanetToxicEntity>(planetX, planetY, Colors::ToxicAtmosphere(), pRadius, pRadius, score["toxic"], atmosphere["toxic"], "Type: Toxic");
        else if (currentSlide == 8) addEntity<PlanetIceEntity>(planetX, planetY, Colors::IceAtmosphere(), pRadius, pRadius, score["ice"], atmosphere["ice"], "Type: Ice");
        else if (currentSlide == 9) addEntity<PlanetLavaEntity>(planetX, planetY, Colors::LavaAtmosphere(), pRadius, pRadius, score["lava"], atmosphere["lava"], "Type: Lava");


        int dialogX = 70;
        int dialogY = 130;
        int yIncr = 55;

        int keyWidth = 50;
        int keyHeight = 50;
        string moveLeft = "textures/keys/LeftArrow.png";
        string moveRight = "textures/keys/RightArrow.png";
        string pause = "textures/keys/P.png";
        string jump = "textures/keys/Space.png";
        int textOffset = 75;


        // Info about things
        switch (currentSlide){
        case 1:
            // slide 1 level info
            addEntity<TextUIEntity>(Fonts::Roboto(50), dialogX, dialogX, Color::White(), "Help 1: The beginning");

            addEntity<TextUIEntity>(Fonts::Roboto(), dialogX, dialogY + (yIncr * 1), Color::White(), "When starting a new level, you first choose a difficulty.");
            addEntity<TextUIEntity>(Fonts::Roboto(), dialogX, dialogY + (yIncr * 2), Color::White(), "Harder levels are generated with more dangerous planets than easier levels.");
            addEntity<TextUIEntity>(Fonts::Roboto(), dialogX, dialogY + (yIncr * 3), Color::White(), "This makes the level less survivable, but makes it yield more resources.");

            addEntity<TextUIEntity>(Fonts::Roboto(), dialogX, dialogY + (yIncr * 5), Color::White(), "Use the");
            addEntity<SpriteEntity>(pause, textOffset + dialogX, dialogY + (yIncr * 5) - (keyHeight / 4), Color::White(), keyWidth, keyHeight);
            addEntity<TextUIEntity>(Fonts::Roboto(), textOffset + keyWidth + dialogX, dialogY + (yIncr * 5), Color::White(), "  key in-game to open a menu.");

            addEntity<TextUIEntity>(Fonts::Roboto(), dialogX, dialogY + (yIncr * 6), Color::White(), "Each time when you return to the menu, the game gets saved.");
            addEntity<TextUIEntity>(Fonts::Roboto(), dialogX, dialogY + (yIncr * 7), Color::White(), "So you can return later to play further.");

            addEntity<TextUIEntity>(Fonts::Roboto(), dialogX, dialogY + (yIncr * 9), Color::White(), "When you're gameover your save gets deleted, but your resources are saved.");
            addEntity<TextUIEntity>(Fonts::Roboto(), dialogX, dialogY + (yIncr * 10), Color::White(), "You can later use these resources in the shop to buy upgrades for your player (not available yet).");

            break;
        case 2:
            // slide 2 movement right/left & jumping
            addEntity<TextUIEntity>(Fonts::Roboto(50),dialogX, dialogX, Color::White(), "Help 2: Moving & jumping");

            addEntity<TextUIEntity>(Fonts::Roboto(), dialogX, dialogY + (yIncr * 1), Color::White(), "By using the wonders of your legs you are able to move around a planet.");

            addEntity<TextUIEntity>(Fonts::Roboto(), dialogX, dialogY + (yIncr * 2), Color::White(), "Use the");
            addEntity<SpriteEntity>(moveLeft, textOffset + dialogX, dialogY + (yIncr * 2) - (keyHeight / 4), Color::White(), keyWidth, keyHeight);
            addEntity<TextUIEntity>(Fonts::Roboto(), textOffset + keyWidth + dialogX, dialogY + (yIncr * 2), Color::White(), "  key to move left.");

            addEntity<TextUIEntity>(Fonts::Roboto(), dialogX, dialogY + (yIncr * 3), Color::White(), "Use the");
            addEntity<SpriteEntity>(moveRight, textOffset + dialogX, dialogY + (yIncr * 3) - (keyHeight / 4), Color::White(), keyWidth, keyHeight);
            addEntity<TextUIEntity>(Fonts::Roboto(), textOffset + keyWidth + dialogX, dialogY + (yIncr * 3), Color::White(), "  key to move right.");

            
            addEntity<TextUIEntity>(Fonts::Roboto(), dialogX, dialogY + (yIncr * 5), Color::White(), "Getting off the planet, using only your legs, is not enough.");
            addEntity<TextUIEntity>(Fonts::Roboto(), dialogX, dialogY + (yIncr * 6), Color::White(), "Try using your jetpack to jump.");

            keyWidth *= 2; // Spacebar is double the width (TODO: add another modifier for each key texture (1 for normal keys, 2 for space, shift, etc.))
            addEntity<TextUIEntity>(Fonts::Roboto(), dialogX, dialogY + (yIncr * 7), Color::White(), "Use the");
            addEntity<SpriteEntity>(jump, textOffset + dialogX, dialogY + (yIncr * 7) - (keyHeight / 4), Color::White(), keyWidth, keyHeight);
            addEntity<TextUIEntity>(Fonts::Roboto(), textOffset + keyWidth + dialogX, dialogY + (yIncr * 7), Color::White(), "  key to jump.");
            keyWidth /= 2;

            addEntity<TextUIEntity>(Fonts::Roboto(), dialogX, dialogY + (yIncr * 9), Color::White(), "However when you are moving through space, there is nothing stopping you from moving further away.");
            addEntity<TextUIEntity>(Fonts::Roboto(), dialogX, dialogY + (yIncr * 10), Color::White(), "So be wise with the choice of trajectory from the planet through endless empty space...");

            break;
        case 3:
            // slide 3 UI

            addEntity<TextUIEntity>(Fonts::Roboto(50), dialogX, dialogX, Color::White(), "Help 3: Resources, Oxygen and Score");

            addEntity<TextUIEntity>(Fonts::Roboto(), dialogX, dialogY + (yIncr * 1), Color::White(), "This is your resource inventory:");

            addEntity<SpriteEntity>("textures/resources-hud.png", dialogX, dialogY + (yIncr * 2), Color::White(), 401.f, 169.f, 100u);
            addEntity<ResourceUIEntity>(dialogX + 41.f, dialogY + (yIncr * 2) + 120.f, Color::White(), "uranium");
            addEntity<ResourceUIEntity>(dialogX + 132.f, dialogY + (yIncr * 2) + 120.f, Color::White(), "diamond");
            addEntity<ResourceUIEntity>(dialogX + 223.f, dialogY + (yIncr * 2) + 120.f, Color::White(), "metal");
            addEntity<ResourceUIEntity>(dialogX + 314.f, dialogY + (yIncr * 2) + 120.f, Color::White(), "anti-matter");

            addEntity<TextUIEntity>(Fonts::Roboto(), dialogX, dialogY + (yIncr * 6), Color::White(), "The resources you collect in-game are added to your total resources when the level is over.");


            addEntity<TextUIEntity>(Fonts::Roboto(), dialogX, dialogY + (yIncr * 8), Color::White(), "This is your oxygentank:");
            addEntity<OxygenUIEntity>(dialogX + 20.f, dialogY + (yIncr * 9));
            addEntity<TextUIEntity>(Fonts::Roboto(), dialogX, dialogY + (yIncr * 10), Color::White(), "The increase and decrease of oxygen can vary between planets.");
            addEntity<TextUIEntity>(Fonts::Roboto(), dialogX, dialogY + (yIncr * 11), Color::White(), "The level is over when there is no oxygen left.");

            addEntity<TextUIEntity>(Fonts::Roboto(), dialogX, dialogY + (yIncr * 13), Color::White(), "This is your score:");
            addEntity<ScoreUIEntity>(dialogX, dialogY + (yIncr * 14));
            addEntity<TextUIEntity>(Fonts::Roboto(), dialogX, dialogY + (yIncr * 15), Color::White(), "Try to get as much as possible and compare it with your friends.");

            break;
        case 4:
            // slide 4 earth

            addEntity<TextUIEntity>(Fonts::Roboto(50), dialogX, dialogX, Color::White(), "Help 4: Planet Earth");

            addEntity<TextUIEntity>(Fonts::Roboto(), dialogX, dialogY + (yIncr * 1), Color::White(), "This planet is a safe-zone.");
            addEntity<TextUIEntity>(Fonts::Roboto(), dialogX, dialogY + (yIncr * 2), Color::White(), "It is mostly spawned in the middle belt of the planetary system.");
            addEntity<TextUIEntity>(Fonts::Roboto(), dialogX, dialogY + (yIncr * 3), Color::White(), "Safe to land on: Yes");
            addEntity<TextUIEntity>(Fonts::Roboto(), dialogX, dialogY + (yIncr * 4), Color::White(), "Score increase: " + to_string(score["earth"]));
            addEntity<TextUIEntity>(Fonts::Roboto(), dialogX, dialogY + (yIncr * 5), Color::White(), "Oxygen: " + string((atmosphere["earth"] >= 1)? "Increase" : (atmosphere["earth"] >= -1)? "Decrease" : "Heavy decrease"));

            break;
        case 5:
            // slide 5 moon

            addEntity<TextUIEntity>(Fonts::Roboto(50), dialogX, dialogX, Color::White(), "Help 5: Planet Moon");

            addEntity<TextUIEntity>(Fonts::Roboto(), dialogX, dialogY + (yIncr * 1), Color::White(), "This planet is mostly a way to other planets.");
            addEntity<TextUIEntity>(Fonts::Roboto(), dialogX, dialogY + (yIncr * 2), Color::White(), "It is mostly spawned in the inner belt of the planetary system, or in the asteroid belts.");
            addEntity<TextUIEntity>(Fonts::Roboto(), dialogX, dialogY + (yIncr * 3), Color::White(), "Safe to land on: Yes");
            addEntity<TextUIEntity>(Fonts::Roboto(), dialogX, dialogY + (yIncr * 4), Color::White(), "Score increase: " + to_string(score["moon"]));
            addEntity<TextUIEntity>(Fonts::Roboto(), dialogX, dialogY + (yIncr * 5), Color::White(), "Oxygen: Decrease");

            break;
        case 6:
            // slide 6 sand

            addEntity<TextUIEntity>(Fonts::Roboto(50), dialogX, dialogX, Color::White(), "Help 6: Planet Sand");

            addEntity<TextUIEntity>(Fonts::Roboto(), dialogX, dialogY + (yIncr * 1), Color::White(), "This planet is partly a safe zone, watch out for the mummies!");
            addEntity<TextUIEntity>(Fonts::Roboto(), dialogX, dialogY + (yIncr * 2), Color::White(), "It is mostly spawned in the inner belt of the planetary system.");
            addEntity<TextUIEntity>(Fonts::Roboto(), dialogX, dialogY + (yIncr * 3), Color::White(), "Safe to land on: Yes");
            addEntity<TextUIEntity>(Fonts::Roboto(), dialogX, dialogY + (yIncr * 4), Color::White(), "Score increase: " + to_string(score["sand"]));
            addEntity<TextUIEntity>(Fonts::Roboto(), dialogX, dialogY + (yIncr * 5), Color::White(), "Oxygen: " + string((atmosphere["sand"] >= 1) ? "Increase" : (atmosphere["sand"] >= -1) ? "Decrease" : "Heavy decrease"));

            break;
        case 7:
            // slide 7 toxic

            addEntity<TextUIEntity>(Fonts::Roboto(50), dialogX, dialogX, Color::White(), "Help 7: Planet Toxic");

            addEntity<TextUIEntity>(Fonts::Roboto(), dialogX, dialogY + (yIncr * 1), Color::White(), "This planet is dangerous, don't stay here too long!");
            addEntity<TextUIEntity>(Fonts::Roboto(), dialogX, dialogY + (yIncr * 2), Color::White(), "It is mostly spawned in the outer belt of the planetary system.");
            addEntity<TextUIEntity>(Fonts::Roboto(), dialogX, dialogY + (yIncr * 3), Color::White(), "Safe to land on: Yes");
            addEntity<TextUIEntity>(Fonts::Roboto(), dialogX, dialogY + (yIncr * 4), Color::White(), "Score increase: " + to_string(score["toxic"]));
            addEntity<TextUIEntity>(Fonts::Roboto(), dialogX, dialogY + (yIncr * 5), Color::White(), "Oxygen: " + string((atmosphere["toxic"] >= 1) ? "Increase" : (atmosphere["toxic"] >= -1) ? "Decrease" : "Heavy decrease"));

            break;
        case 8:
            // slide 8 ice

            addEntity<TextUIEntity>(Fonts::Roboto(50), dialogX, dialogX, Color::White(), "Help 8: Planet Ice");

            addEntity<TextUIEntity>(Fonts::Roboto(), dialogX, dialogY + (yIncr * 1), Color::White(), "This planet is partly a safe zone, watch out for the snowmen!");
            addEntity<TextUIEntity>(Fonts::Roboto(), dialogX, dialogY + (yIncr * 2), Color::White(), "It is mostly spawned in the outer belt of the planetary system.");
            addEntity<TextUIEntity>(Fonts::Roboto(), dialogX, dialogY + (yIncr * 3), Color::White(), "Safe to land on: Yes");
            addEntity<TextUIEntity>(Fonts::Roboto(), dialogX, dialogY + (yIncr * 4), Color::White(), "Score increase: " + to_string(score["ice"]));
            addEntity<TextUIEntity>(Fonts::Roboto(), dialogX, dialogY + (yIncr * 5), Color::White(), "Oxygen: " + string((atmosphere["ice"] >= 1) ? "Increase" : (atmosphere["ice"] >= -1) ? "Decrease" : "Heavy decrease"));


            break;
        case 9:
            // slide 8 lava

            addEntity<TextUIEntity>(Fonts::Roboto(50), dialogX, dialogX, Color::White(), "Help 9: Planet Lava");

            addEntity<TextUIEntity>(Fonts::Roboto(), dialogX, dialogY + (yIncr * 1), Color::White(), "This planet is highly dangerous!");
            addEntity<TextUIEntity>(Fonts::Roboto(), dialogX, dialogY + (yIncr * 2), Color::White(), "It is mostly spawned in the middle or the inner belt of the planetary system.");
            addEntity<TextUIEntity>(Fonts::Roboto(), dialogX, dialogY + (yIncr * 3), Color::White(), "Safe to land on: No");

            break;
        default:
            break;
        }

        if(currentSlide != 9) addEntity<PlayerEntity>(planetX + (pRadius / 2), planetY - 50, Color::White(), 25.f, 50.f, 1.0f, false);

    }

    void HelpScene::sceneEnd()
    {
        getTransitionManager().getAudioDevice().stopSoundEffect("");
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
