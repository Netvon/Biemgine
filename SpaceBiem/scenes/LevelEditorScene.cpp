#include "stdafx.h"

#include "LevelEditorScene.h"
#include "MenuScene.h"
#include "LevelScene.h"
#include "LevelLoadScene.h"

#include "..\entities\ButtonUIEntity.h"
#include "../entities/PlanetEarthEntity.h"
#include "../entities/PlanetMoonEntity.h"

#include "..\globals\Fonts.h"

using biemgine::TextUIEntity;
using biemgine::SpriteEntity;
using biemgine::FileHandler;


namespace spacebiem
{

    void LevelEditorScene::created()
    {
        enableRendering();
        enableUI();
        enableScripts();

        int wW = getTransitionManager().getWindowWidth();
        int wH = getTransitionManager().getWindowHeight();
        float planetWidth = 500;
        float planetHeight = 500;

        addEntity<SpriteEntity>("textures/spacebiem.png", wW / 2 - 175, 100, Color::White(), -1, -1);
        addEntity<PlanetEarthEntity>(-100.f, static_cast<float>(wH - 200), Color{ 71, 166, 245, 255 }, planetWidth, planetHeight, 0, 10.f);
        addEntity<PlanetMoonEntity>(static_cast<float>(wW - 250), static_cast<float>(wH - 250), Color::White(), planetWidth, planetHeight, 0);

        auto buttonTexture = "textures/button_white.png";
        auto buttonColor = Color{ 35, 65, 112 };
        auto buttonTextColor = Color::White();
        auto buttonSize = Size{ 150, 50 };


        addEntity<ButtonUIEntity>((wW / 2) - (buttonSize.width / 2), wH - 250, buttonColor, buttonTextColor, buttonSize, "Back to slots", buttonTexture,
            [this](StateManager* manager)
        {
            manager->navigateTo<LevelLoadScene>();
        });

    }

    void LevelEditorScene::input()
    {
        if (im.isKeyDown("Q")) {
            signalQuit();
        }

        if (im.isKeyDown("Backspace")) {
            getTransitionManager().navigateTo<MenuScene>();
        }
    }

    void LevelEditorScene::update()
    {
        updateEntities();
    }

    void LevelEditorScene::render(const float deltaTime)
    {
        getTransitionManager().drawBackground("textures/space.png");
        updateEntities(deltaTime);
    }
}
