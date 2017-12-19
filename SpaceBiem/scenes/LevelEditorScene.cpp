#include "stdafx.h"

#include "LevelEditorScene.h"
#include "MenuScene.h"
#include "LevelScene.h"
#include "LevelLoadScene.h"

#include "..\entities\ButtonUIEntity.h"
#include "../entities/PlanetEarthEntity.h"
#include "../entities/PlanetMoonEntity.h"

#include "../systems/DragDropSystem.h"

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

        addSystem<DragDropSystem>();

        int wW = getTransitionManager().getWindowWidth();
        int wH = getTransitionManager().getWindowHeight();
        float planetWidth = 500;
        float planetHeight = 500;

        auto buttonTexture = "textures/button_white.png";
        auto buttonColor = Color{ 35, 65, 112 };
        auto buttonTextColor = Color::White();
        auto buttonSize = Size{ 150, 50 };

        int menuSize = 400;

        // menu background
        addEntity<SpriteEntity>("textures/rectangle.png", wW - menuSize, 0, Color{ 0, 0, 0, 150 }, menuSize, wH, 1u, "entity_menu");


        fillMenuEntitySpace();


        addEntity<ButtonUIEntity>((wW) - (buttonSize.width) - 20, wH - buttonSize.height - 20, buttonColor, buttonTextColor, buttonSize, "Back to slots", buttonTexture,
            [this](StateManager* manager)
        {
            manager->navigateTo<LevelLoadScene>();
        });

    }


    void LevelEditorScene::fillMenuEntitySpace() {

        int wW = getTransitionManager().getWindowWidth();
        int wH = getTransitionManager().getWindowHeight();

        int menuSize = 400;

        int entityMarginX = 80;
        int entityMarginY = 80;
        int entityWidth = (menuSize - (entityMarginX * 2));

        addEntity<PlanetEarthEntity>(wW - entityMarginX - (entityWidth), entityMarginY, Color{ 71, 166, 245, 255 }, entityWidth / 2, entityWidth / 2, 0, 10.f);



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
