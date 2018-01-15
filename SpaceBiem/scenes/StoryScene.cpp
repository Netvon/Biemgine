#include "stdafx.h"
#include "StoryScene.h"
#include "LevelScene.h"

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

        int wW = getTransitionManager().getWindowWidth();
        int wH = getTransitionManager().getWindowHeight();
        float planetWidth = 500;
        float planetHeight = 500;
        int w = 50;
        int x = wW / 2;

        addEntity<PlanetEarthEntity>(-250.f, static_cast<float>(wH - 250), Color({ 71, 166, 245, 255 }), planetWidth, planetHeight, 0, 10.f);
        addEntity<PlanetMoonEntity>(static_cast<float>(wW - 250), static_cast<float>(wH - 250), Color::White(), planetWidth, planetHeight, 0);

        int overlayId = addEntity<SpriteEntity>("textures/rectangle.png", 0, 0, Color{ 0, 0, 0, 0 }, wW, wH, 9999);
        auto overlayEntity = getEntity(overlayId);
        overlayEntity->addComponent("animation", new AnimationComponent(255, 0, 500,
            [sprite = overlayEntity->getComponent<TextureComponent>("texture")](float newValue) { sprite->setColor(sprite->getColor().WithAlpha(newValue)); }, nullptr, false));
        auto overlayAnimation = overlayEntity->getComponent<AnimationComponent>("animation");

        auto buttonTexture = "textures/button_white.png";
        auto buttonColor = Color{ 35, 65, 112 };
        auto buttonTextColor = Color::White();
        auto buttonSize = Size{ 150, 50 };

        if (nextDifficulty == Difficulty::NORMAL)
        {
            addEntity<TextUIEntity>(Fonts::Roboto(40), wW / 2, 80, Color::White(), "The next level is has a normal difficulty", true);

            addEntity<ButtonUIEntity>(x - 25, 300, Color{ 22, 94, 22 }, buttonTextColor, buttonSize, "Normal", buttonTexture,
                [overlayAnimation](StateManager* manager)
            {
                manager->navigateTo<LevelScene>(Difficulty::NORMAL);
                overlayAnimation->play();
            });
        }
        else if (nextDifficulty == Difficulty::CHALLENING)
        {
            addEntity<TextUIEntity>(Fonts::Roboto(40), wW / 2, 80, Color::White(), "The next level is has a challenging difficulty", true);
        }
        else if (nextDifficulty == Difficulty::EXPERT)
        {
            addEntity<TextUIEntity>(Fonts::Roboto(40), wW / 2, 80, Color::White(), "The next level is has a export difficulty", true);
        }
        else
        {
            addEntity<TextUIEntity>(Fonts::Roboto(40), wW / 2, 80, Color::White(), "You have completed the expert difficulty", true);
            addEntity<TextUIEntity>(Fonts::Roboto(40), wW / 2, 100, Color::White(), "You have finished the game!", true);
        }
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
