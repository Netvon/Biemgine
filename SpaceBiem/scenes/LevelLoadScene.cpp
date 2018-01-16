#include "stdafx.h"

#include "LevelLoadScene.h"
#include "MenuScene.h"
#include "LevelScene.h"
#include "LevelEditorScene.h"

#include "..\entities\ButtonUIEntity.h"
#include "../entities/PlanetEarthEntity.h"
#include "../entities/PlanetMoonEntity.h"

#include "..\globals\Fonts.h"

using biemgine::TextUIEntity;
using biemgine::SpriteEntity;
using biemgine::FileHandler;


namespace spacebiem
{

    void LevelLoadScene::created()
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

        int buttonMargin = 30;
        int xMargin = 550;
        int yMargin = 300;

        int yButtons = 2;
        int xButtons = 3;

        int buttonW = (wW - (xMargin * 2) - (buttonMargin * (xButtons - 1))) / xButtons;
        int buttonH = (wH - (yMargin * 2) - (buttonMargin * (yButtons - 1))) / yButtons;

        FileHandler fh{ "" };

        int betweenButtonMargin = 5;

        for (int y = 0; y < yButtons; y++) {
            for (int x = 1; x <= xButtons; x++) {
                int slotN = ((y)* xButtons) + x;

                if (fh.exists("data/level_slot_" + to_string(slotN) + ".csv")) {

                    int smallH = (buttonH / 3);

                    addEntity<ButtonUIEntity>(xMargin + ((x - 1) * (buttonW + buttonMargin)), yMargin + (y * (buttonH + buttonMargin)) + (0 * (smallH + betweenButtonMargin)), Color{ 22, 94, 22 }, buttonTextColor, Size{ buttonW, smallH }, "Play level", buttonTexture,
                        [slotN](StateManager* manager)
                    {
                        manager->navigateTo<LevelScene>(false, Difficulty::NORMAL, "data/level_slot_" + to_string(slotN) + ".csv");
                    });

                    addEntity<ButtonUIEntity>(xMargin + ((x - 1) * (buttonW + buttonMargin)), yMargin + (y * (buttonH + buttonMargin)) + (1 * (smallH + betweenButtonMargin)), Color{ 188, 103, 0 }, buttonTextColor, Size{ buttonW, smallH }, "Edit level", buttonTexture,
                        [slotN](StateManager* manager)
                    {
                        manager->navigateTo<LevelEditorScene>("data/level_slot_" + to_string(slotN) + ".csv");
                    });

                    addEntity<ButtonUIEntity>(xMargin + ((x - 1) * (buttonW + buttonMargin)), yMargin + (y * (buttonH + buttonMargin)) + (2 * (smallH + betweenButtonMargin)), Color{ 135, 25, 25 }, buttonTextColor, Size{ buttonW, smallH }, "Delete level", buttonTexture,
                        [slotN](StateManager* manager)
                    {
                        FileHandler fh{ "" };
                        fh.remove("data/level_slot_" + to_string(slotN) + ".csv");
                        manager->navigateTo<LevelLoadScene>();
                    });

                }
                else {
                    addEntity<ButtonUIEntity>(xMargin + ((x - 1) * (buttonW + buttonMargin)), yMargin + (y * (buttonH + buttonMargin)), buttonColor, buttonTextColor, Size{ buttonW, buttonH }, "Create new level", buttonTexture,
                        [slotN](StateManager* manager)
                    {
                        FileHandler fh{ "data/level_slot_" + to_string(slotN) + ".csv" };
                        fh.writeLine("");
                        manager->navigateTo<LevelLoadScene>();
                    });
                }
            }
        }

        addEntity<ButtonUIEntity>((wW / 2) - (buttonSize.width / 2), wH - 250, buttonColor, buttonTextColor, buttonSize, "Menu", buttonTexture,
            [this](StateManager* manager)
        {
            manager->navigateTo<MenuScene>();
        });

    }

    void LevelLoadScene::input()
    {
        if (im.isKeyDown("Q")) {
            signalQuit();
        }

        if (im.isKeyDown("Backspace")) {
            getTransitionManager().navigateTo<MenuScene>();
        }
    }

    void LevelLoadScene::update()
    {
        updateEntities();
    }

    void LevelLoadScene::render(const float deltaTime)
    {
        getTransitionManager().drawBackground("textures/space.png");
        updateEntities(deltaTime);
    }
}
