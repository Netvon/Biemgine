#include "stdafx.h"

#include "DifficultyScene.h"
#include "MenuScene.h"
#include "LevelScene.h"
#include "StoryScene.h"

#include "..\entities\PlanetEarthEntity.h"
#include "..\entities\PlanetMoonEntity.h"

#include "..\entities\ButtonUIEntity.h"

#include "..\globals\Fonts.h"
#include "..\globals\Difficulty.h"

#include "..\FileParser.h"

using biemgine::AnimationComponent;
using biemgine::TextureComponent;
using biemgine::TextUIEntity;
using biemgine::SpriteEntity;

namespace spacebiem
{

    void DifficultyScene::created()
    {
        enableRendering();
        enableUI();
        enableScripts();
        enableAnimations();

        int wW = getTransitionManager().getWindowWidth();
        int wH = getTransitionManager().getWindowHeight();
        float planetWidth = 500;
        float planetHeight = 500;
        float playerWidth = 15 * 2;
        float playerHeight = 25 * 2;
        int w = 50;
        int x = wW / 2 - w;

        FileParser fp;
        progress = fp.progressContent();

       /* int overlayId = addEntityExtra<SpriteEntity>([](Entity* entity)
        {
            entity->addComponent("animation", new AnimationComponent(0, 255, 300.f, [sprite = entity->getComponent<TextureComponent>("texture")](float newValue) { sprite->setColor(sprite->getColor().WithAlpha(newValue)); }, nullptr, false));
        }, "textures/rectangle.png", 0, 0, Color{0, 0, 0, 0}, wW, wH, 9999);

        auto overlayEntity = getEntity(overlayId);
        auto overlayAnimation = overlayEntity->getComponent<AnimationComponent>("animation");*/

        addEntity<SpriteEntity>("textures/choose_difficulty.png", wW / 2 - 175, 130, Color::White(), -1, -1);
        addEntity<PlanetEarthEntity>(-250.f, static_cast<float>(wH - 250), Color({ 71, 166, 245, 255 }), planetWidth, planetHeight, 0, 10.f);
        addEntity<PlanetMoonEntity>(static_cast<float>(wW - 250), static_cast<float>(wH - 250), Color::White(), planetWidth, planetHeight, 0);

        auto buttonTexture = "textures/button_white.png";
        auto buttonColor = Color{ 35, 65, 112 };
        auto buttonTextColor = Color::White();
        auto buttonSize = Size{ 150, 50 };

        int beginY = 280;
        int incr = 65;

        std::function<void(StateManager*)> normal = nullptr;
        std::function<void(StateManager*)> challenging = nullptr;
        std::function<void(StateManager*)> expert = nullptr;

        if (progress[Difficulty::NORMAL]) {
            normal = [](StateManager* manager)
            {
                //auto nextAvail = static_cast<Difficulty>(static_cast<int>(Difficulty::NORMAL) + 1);
                manager->navigateTo<StoryScene>(Difficulty::NORMAL);
            };
        }

        if (progress[Difficulty::CHALLENING]) {
            challenging = [](StateManager* manager)
            {
                //auto nextAvail = static_cast<Difficulty>(static_cast<int>(Difficulty::NORMAL) + 1);
                manager->navigateTo<StoryScene>(Difficulty::CHALLENING);
            };
        }

        if (progress[Difficulty::EXPERT]) {
            expert = [](StateManager* manager)
            {
                //auto nextAvail = static_cast<Difficulty>(static_cast<int>(Difficulty::NORMAL) + 1);
                manager->navigateTo<StoryScene>(Difficulty::EXPERT);
            };
        }


        addEntity<ButtonUIEntity>(x - 25, beginY + (0 * incr), Color{ 22, 94, 22 }, buttonTextColor, buttonSize, "Normal", buttonTexture, normal);

        addEntity<ButtonUIEntity>(x - 25, beginY + (1 * incr), Color{ 188, 103, 0 }, buttonTextColor, buttonSize, "Challenging", buttonTexture, challenging);

        addEntity<ButtonUIEntity>(x - 25, beginY + (2 * incr), Color{ 135, 25, 25 }, buttonTextColor, buttonSize, "Expert", buttonTexture, expert);

        beginY += 40;
        addEntity<ButtonUIEntity>(x - 25, beginY + (3 * incr), buttonColor, buttonTextColor, buttonSize, "Menu", buttonTexture,
            [this](StateManager* manager)
        {
            manager->navigateTo<MenuScene>();
        });
    }

    void DifficultyScene::input()
    {
        if (im.isKeyDown("Q")) {
            signalQuit();
        }

        if (im.isKeyDown("Backspace")) {
            getTransitionManager().navigateTo<MenuScene>();
        }
    }

    void DifficultyScene::update()
    {
        updateEntities();
    }

    void DifficultyScene::render(const float deltaTime)
    {
        getTransitionManager().drawBackground("textures/space.png");
        updateEntities(deltaTime);
    }
}
