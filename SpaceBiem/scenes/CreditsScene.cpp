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
using biemgine::TextComponent;

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
        int x = wW / 2;

        addEntity<SpriteEntity>("textures/teambiem.png", static_cast<float>(wW / 2 - 500.f), 10.f, Color::White(), -1, -1, 100u);
        addEntity<SpriteEntity>("textures/spacebiem.png", static_cast<float>(wW / 2 + 200.f), 10.f, Color::White(), -1, -1, 100u);

        auto thanksToTextId = addEntity<TextUIEntity>(Fonts::Roboto(), x, 200, Color{ 232, 228, 41 }, "Thanks to:", true);
        getEntity(thanksToTextId)->getComponent<TextComponent>("text")->setColor(Color{ 232, 228, 41 });

        addEntity<TextUIEntity>(Fonts::Roboto(), x, 250, Color::White(), "Tom van Nimwegen", true);
        addEntity<TextUIEntity>(Fonts::Roboto(), x, 275, Color::White(), "Luuk Spierings", true);
        addEntity<TextUIEntity>(Fonts::Roboto(), x, 300, Color::White(), "Kevin Schuurmans", true);
        addEntity<TextUIEntity>(Fonts::Roboto(), x, 325, Color::White(), "Stijn Mommersteeg", true);
        addEntity<TextUIEntity>(Fonts::Roboto(), x, 350, Color::White(), "Sjonnie Immink", true);
        addEntity<TextUIEntity>(Fonts::Roboto(), x, 375, Color::White(), "Willy van Eck", true);

        addEntity<TextUIEntity>(Fonts::Roboto(), x, 450, Color{ 232, 228, 41 }, "Packages: ", true);
        addEntity<SpriteEntity>("textures/SDL_logo.png", static_cast<float>(x - 100), 425.f, Color::White(), -1, -1, 100u);
        addEntity<SpriteEntity>("textures/box2d.png", static_cast<float>(x - 100), 575.f, Color::White(), -1, -1, 100u);

        auto testerTextId = addEntity<TextUIEntity>(Fonts::Roboto(), x, 700, Color::White(), "Special thanks to all testers", true);
        getEntity(testerTextId)->getComponent<TextComponent>("text")->setColor(Color{ 232, 228, 41 });

        addEntity<TextUIEntity>(Fonts::Roboto(), x, 800, Color::White(), "Copyright 2017 Team Biem, Release 11-12-2017", true);

        addEntity<PlanetEarthEntity>(-250.f, static_cast<float>(wH - 250), Color({ 71, 166, 245, 255 }), planetWidth, planetHeight, 0, 10.f);
        addEntity<PlanetMoonEntity>(static_cast<float>(wW - 250), static_cast<float>(wH - 250), Color::White(), planetWidth, planetHeight, 0);

        auto buttonTexture = "textures/button_white.png";
        auto buttonColor = Color{ 35, 65, 112 };
        auto buttonTextColor = Color::White();
        auto buttonSize = Size{ 150, 50 };

        addEntity<ButtonUIEntity>(x - 75, 875, buttonColor, buttonTextColor, buttonSize, "Menu", buttonTexture, CreditsMenuButtonClicked, onCreditsButtonEntered);
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
