#include "stdafx.h"
#include "StoryScene.h"
#include "LevelScene.h"
#include "DifficultyScene.h"

#include "..\entities\PlanetEarthEntity.h"
#include "..\entities\AdEntity.h"
#include "..\entities\PlanetMoonEntity.h"

#include "..\entities\ButtonUIEntity.h"

#include "..\globals\Fonts.h"
#include "..\globals\Colors.h"

using biemgine::AnimationComponent;
using biemgine::TextureComponent;
using biemgine::TextUIEntity;
using biemgine::SpriteEntity;

namespace spacebiem
{
    void StoryScene::created() {
        enableRendering();
        enableUI();
        enableScripts();
        enableAnimations();

        int wW = getTransitionManager().getWindowWidth();
        int wH = getTransitionManager().getWindowHeight();
        float planetWidth = 500;
        float planetHeight = 500;
        int w = 50;
        int x = wW / 2;

        addEntity<AdEntity>();

        addEntity<PlanetEarthEntity>(-250.f, static_cast<float>(wH - 250), Color({ 71, 166, 245, 255 }), planetWidth, planetHeight, 0, 10.f);
        addEntity<PlanetMoonEntity>(static_cast<float>(wW - 250), static_cast<float>(wH - 250), Color::White(), planetWidth, planetHeight, 0);

        int overlayId = addEntityExtra<SpriteEntity>([](Entity* entity)
        {
            entity->addComponent("animation", new AnimationComponent(255, 0, 300.f, [sprite = entity->getComponent<TextureComponent>("texture")](float newValue) { sprite->setColor(sprite->getColor().WithAlpha(newValue)); }, nullptr, false));
        }, "textures/rectangle.png", 0, 0, Color{ 0, 0, 0, 0 }, wW, wH, 9999);

        auto overlayEntity = getEntity(overlayId);
        auto overlayAnimation = overlayEntity->getComponent<AnimationComponent>("animation");

        auto buttonTexture = "textures/button_white.png";
        auto buttonColor = Color{ 35, 65, 112 };
        auto buttonTextColor = Color::White();
        auto buttonSize = Size{ 150, 50 };

        if (nextDifficulty != Difficulty::DONE)
        {
            addEntity<ButtonUIEntity>(x - 75, 300, buttonColor, buttonTextColor, buttonSize, "Play", buttonTexture,
                [this, overlayAnimation](StateManager* manager)
            {
                overlayAnimation->setOnFinished([this, manager] {manager->navigateTo<LevelScene>(true, nextDifficulty); });
                overlayAnimation->playReversed();
            });

            if (nextDifficulty == Difficulty::NORMAL)
            {
                addEntity<TextUIEntity>(Fonts::Roboto(40), wW / 2, 80, Color::White(), "This is a story of a man named BiemBoii", true);
                addEntity<TextUIEntity>(Fonts::Roboto(40), wW / 2, 140, Color::White(), "Get to the wormhole to proceed to the next level", true);
                addEntity<TextUIEntity>(Fonts::Roboto(), wW / 2, 200, Color::White(), "The next level has a normal difficulty", true);
            }
            else if (nextDifficulty == Difficulty::CHALLENING)
            {
                addEntity<TextUIEntity>(Fonts::Roboto(40), wW / 2, 80, Color::White(), "This is a story of a man named BiemBoii", true);
                addEntity<TextUIEntity>(Fonts::Roboto(40), wW / 2, 140, Color::White(), "Get to the wormhole to proceed to the next level", true);
                addEntity<TextUIEntity>(Fonts::Roboto(), wW / 2, 200, Color::White(), "The next level has a challenging difficulty", true);
            }
            else if (nextDifficulty == Difficulty::EXPERT)
            {
                addEntity<TextUIEntity>(Fonts::Roboto(40), wW / 2, 80, Color::White(), "This is a story of a man named BiemBoii", true);
                addEntity<TextUIEntity>(Fonts::Roboto(40), wW / 2, 140, Color::White(), "Get to the wormhole to proceed to the next level", true);
                addEntity<TextUIEntity>(Fonts::Roboto(), wW / 2, 200, Color::White(), "The next level has a expert difficulty", true);
            }
        } 
        else
        {
            addEntity<TextUIEntity>(Fonts::Roboto(40), wW / 2, 80, Color::White(), "You have completed the expert difficulty", true);
            addEntity<TextUIEntity>(Fonts::Roboto(40), wW / 2, 140, Color::White(), "You have finished the game!", true);
        }

        addEntity<ButtonUIEntity>(x - 75, 365, buttonColor, buttonTextColor, buttonSize, "Back", buttonTexture,
            [](StateManager* manager)
        {
            manager->navigateTo<DifficultyScene>();
        });
    }

    void StoryScene::input()
    {
       
    }

    void StoryScene::update()
    {
        updateEntities();
    }

    void StoryScene::render(const float deltaTime)
    {
        getTransitionManager().drawBackground("textures/space.png");
        updateEntities(deltaTime);
    }
}
