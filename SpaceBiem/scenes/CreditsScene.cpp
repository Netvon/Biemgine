#include "stdafx.h"
#include "CreditsScene.h"
#include "MenuScene.h"

#include "..\entities\PlanetEarthEntity.h"
#include "..\entities\PlanetMoonEntity.h"
#include "..\entities\ButtonUIEntity.h"

#include "..\globals\Fonts.h"

using biemgine::Size;
using biemgine::SpriteEntity;
using biemgine::TextUIEntity;

namespace spacebiem
{
    void CreditsBackButtonClicked(StateManager* e)
    {
        e->getAudioDevice().playSoundEffect("audio/idroid.mp3", 0, -1, 128);
        e->navigateTo<MenuScene>();
    }

    void onCreditsButtonEntered(StateManager* e)
    {
        e->getAudioDevice().playSoundEffect("audio/switch.mp3", 0, -1, 128);
    }

    void CreditsMenuButtonClicked(StateManager* e)
    {
        e->getAudioDevice().playSoundEffect("audio/idroid.mp3", 0, -1, 128);
        e->getAudioDevice().playMusic("audio/menu.mp3", -1);
        e->navigateTo<MenuScene>();
    }


    void CreditsScene::created() {
        enableRendering();
        enableUI();
        enableScripts();

        int wW = getTransitionManager().getWindowWidth();
        int wH = getTransitionManager().getWindowHeight();
        float planetWidth = 500;
        float planetHeight = 500;
        int w = 50;
        int x = wW / 2 - w;

        addEntity<SpriteEntity>("textures/teambiem.png", static_cast<float>(wW / 2 - 500.f), 10.f, Color::White(), -1, -1, 100u);
        addEntity<SpriteEntity>("textures/spacebiem.png", static_cast<float>(wW / 2 + 200.f), 10.f, Color::White(), -1, -1, 100u);

        addEntity<TextUIEntity>(Fonts::Roboto(), x, 200, Color{ 35, 65, 112 }, "Met dank aan:");

        addEntity<TextUIEntity>(Fonts::Roboto(), x, 250, Color{ 66, 143, 244 }, "Tom van Nimwegen");
        addEntity<TextUIEntity>(Fonts::Roboto(), x, 275, Color{ 66, 143, 244 }, "Luuk Spierings");
        addEntity<TextUIEntity>(Fonts::Roboto(), x, 300, Color{ 66, 143, 244 }, "Kevin Schuurmans");
        addEntity<TextUIEntity>(Fonts::Roboto(), x, 325, Color{ 66, 143, 244 }, "Stijn Mommersteeg");
        addEntity<TextUIEntity>(Fonts::Roboto(), x, 350, Color{ 66, 143, 244 }, "Sjonnie Immink");
        addEntity<TextUIEntity>(Fonts::Roboto(), x, 375, Color{ 66, 143, 244 }, "Willy van Eck");

        addEntity<TextUIEntity>(Fonts::Roboto(), x, 450, Color{ 35, 65, 112 }, "Packages: ");
        addEntity<SpriteEntity>("textures/SDL_logo.png", static_cast<float>(x - 25), 425.f, Color::White(), -1, -1, 100u);
        addEntity<SpriteEntity>("textures/box2d.png", static_cast<float>(x), 575.f, Color::White(), -1, -1, 100u);

        addEntity<PlanetEarthEntity>(-250.f, static_cast<float>(wH - 250), Color({ 71, 166, 245, 255 }), planetWidth, planetHeight, 0, 10.f);
        addEntity<PlanetMoonEntity>(static_cast<float>(wW - 250), static_cast<float>(wH - 250), Color::White(), planetWidth, planetHeight, 0);

        auto buttonTexture = "textures/button_white.png";
        auto buttonColor = Color{ 35, 65, 112 };
        auto buttonTextColor = Color::White();
        auto buttonSize = Size{ 150, 50 };

        addEntity<ButtonUIEntity>(x - 25, 875, buttonColor, buttonTextColor, buttonSize, "Menu", buttonTexture, CreditsMenuButtonClicked, onCreditsButtonEntered);
    }

    void CreditsScene::input()
    {
        if (im.isKeyDown("Q")) {
            signalQuit();
        }

        if (im.isKeyDown("Backspace")) {
            getTransitionManager().navigateTo<MenuScene>();
        }
    }

    void CreditsScene::update()
    {
        updateEntities();
    }

    void CreditsScene::render(const float deltaTime)
    {
        getTransitionManager().drawBackground("textures/space.png");
        updateEntities(deltaTime);
    }
}
