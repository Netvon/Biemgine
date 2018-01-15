#include "stdafx.h"
#include "ProfileScene.h"
#include "MenuScene.h"

namespace spacebiem
{
    void ProfileScene::created()
    {
        enableRendering();
        enableUI();
        enableScripts();
        enableAnimations();

        getTransitionManager().getAudioDevice().stopSoundEffect("");

        int wW = getTransitionManager().getWindowWidth();
        int wH = getTransitionManager().getWindowHeight();
        float planetWidth = 500;
        float planetHeight = 500;
        float playerWidth = 15 * 2;
        float playerHeight = 25 * 2;
        int w = 50;
        int x = wW / 2 - 175;

        int overlayId = addEntity<SpriteEntity>("textures/rectangle.png", 0, 0, Color{ 0, 0, 0, 0 }, wW, wH, 9999);
        auto overlayEntity = getEntity(overlayId);
        overlayEntity->addComponent("animation", new AnimationComponent(255, 0, 500,
            [sprite = overlayEntity->getComponent<TextureComponent>("texture")](float newValue) { sprite->setColor(sprite->getColor().WithAlpha(newValue)); }, nullptr, false));
        auto overlayAnimation = overlayEntity->getComponent<AnimationComponent>("animation");

        if (fadeIn)
        {
            overlayAnimation->play();
        }

        addEntity<SpriteEntity>("textures/spacebiem.png", x, 100, Color::White(), -1, -1);
        addEntity<SpriteEntity>("textures/player-standing.png", x + 260, 115, Color::White(), playerWidth, playerHeight);
        addEntity<PlanetEarthEntity>(-250.f, static_cast<float>(wH - 250), Color({ 71, 166, 245, 255 }), planetWidth, planetHeight, 0, 10.f);
        addEntity<PlanetMoonEntity>(static_cast<float>(wW - 250), static_cast<float>(wH - 250), Color::White(), planetWidth, planetHeight, 0);

        auto buttonTexture = "textures/button_white.png";
        auto buttonColor = Color{ 35, 65, 112 };
        auto buttonTextColor = Color::White();
        auto buttonSize = Size{ 150 * 2, 50 * 2 };


        addEntity<ButtonUIEntity>((wW / 2) - (buttonSize.width / 2), wH - 650, buttonColor, buttonTextColor, buttonSize, "Select 'Biem'", buttonTexture,
            [this](StateManager* manager)
        {
            Player::current().setName(Player::playerOne());
            manager->navigateTo<MenuScene>();;
        });

        addEntity<ButtonUIEntity>((wW / 2) - (buttonSize.width / 2), wH - 500, buttonColor, buttonTextColor, buttonSize, "Select 'Mummy'", buttonTexture,
            [this](StateManager* manager)
        {
            Player::current().setName(Player::playerTwo());
            manager->navigateTo<MenuScene>();
        });

        addEntity<ButtonUIEntity>((wW / 2) - (buttonSize.width / 2), wH - 350, buttonColor, buttonTextColor, buttonSize, "Select 'Snowman'", buttonTexture,
            [this](StateManager* manager)
        {
            Player::current().setName(Player::playerThree());
            manager->navigateTo<MenuScene>();
        });

        addEntity<SpriteEntity>("textures/choose_profile.png", (wW / 2) - 192, wH - 750, Color::White(), -1, -1);
    }

    void ProfileScene::update()
    {
        updateEntities();
    }

    void ProfileScene::render(const float deltaTime)
    {
        getTransitionManager().drawBackground("textures/space.png");
        updateEntities(deltaTime);
    }
}
