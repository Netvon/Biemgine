#include "stdafx.h"
#include "WinScene.h"
#include "LevelScene.h"
#include "DifficultyScene.h"

#include "..\entities\PlanetEarthEntity.h"
#include "..\entities\PlayerEntity.h"
#include "..\entities\ButtonUIEntity.h"

#include "../systems/MovementSystem.h"
#include "../systems/GravitySystem.h"
#include "../systems/JumpSystem.h"

#include "../scenes/CreditsScene.h"

#include "..\globals\Fonts.h"
#include "..\globals\Colors.h"

#include "..\FileParser.h"

using biemgine::AnimationComponent;
using biemgine::TextureComponent;
using biemgine::TextUIEntity;
using biemgine::SpriteEntity;

namespace spacebiem
{
    void WinScene::created() {
        enableRendering();
        enablePhysics();
        enableUI();
        enableScripts();
        enableAnimations();

        addSystem<GravitySystem>();
        addSystem<MovementSystem>();
        addSystem<JumpSystem>();

        FileParser parser;
        parser.writeNewResources(resources);

        int wW = getTransitionManager().getWindowWidth();
        int wH = getTransitionManager().getWindowHeight();
        float planetWidth = 500;
        float planetHeight = 500;
        int w = 50;
        int x = wW / 2;

        auto buttonTexture = "textures/button_white.png";
        auto buttonColor = Color{ 35, 65, 112 };
        auto buttonTextColor = Color::White();
        auto buttonSize = Size{ 200, 50 };
        int beginY = 330;
        int incr = 65;

        addEntity<TextUIEntity>(Fonts::Roboto(40), wW / 2, 80, Color::White(), "Congratulations, you have reached your goal!", true);
        addEntity<TextUIEntity>(Fonts::Roboto(40), wW / 2, 140, Color::White(), "Thanks for playing our game :D", true);
        addEntity<ButtonUIEntity>(wW / 2 - 100, 200, buttonColor, buttonTextColor, buttonSize, "Go to the credits", buttonTexture, [this](StateManager* e) { e->navigateTo<CreditsScene>(); }, nullptr);

        int pRadius = 500;
        int planetX = x - pRadius / 2;
        int planetY = 550;
        addEntity<PlanetEarthEntity>(planetX, planetY, Colors::EarthAtmosphere(), pRadius, pRadius, 0, 0, "Type: Earth");
        addEntity<PlayerEntity>(planetX + (pRadius / 2), planetY - 50, Color::White(), 25.f, 50.f, 1.0f, false);

        if (!getTransitionManager().getAudioDevice().isPlayingMusic("audio/menu.mp3"))
            getTransitionManager().getAudioDevice().playMusic("audio/menu.mp3", -1);
    }

    void WinScene::input()
    {
        if (im.isKeyDown("Q")) {
            signalQuit();
        }
    }

    void WinScene::update()
    {
        updateEntities();
    }

    void WinScene::render(const float deltaTime)
    {
        getTransitionManager().drawBackground("textures/space.png");
        updateEntities(deltaTime);
    }
}
