#include "stdafx.h"
#include "ProfileScene.h"
#include "MenuScene.h"
#include "../FileParser.h"
#include "../entities/ResourceUIEntity.h"
#include "../systems/ResourceUISystem.h"

namespace spacebiem
{
    void ProfileScene::created()
    {
        enableRendering();
        enableUI();
        enableScripts();
        enableAnimations();

        addSystem<ResourceUISystem>();

        getTransitionManager().getAudioDevice().stopSoundEffect("");

        int wW = getTransitionManager().getWindowWidth();
        int wH = getTransitionManager().getWindowHeight();
        float planetWidth = 500;
        float planetHeight = 500;
        float playerWidth = 15 * 2;
        float playerHeight = 25 * 2;
        int w = 50;
        int x = wW / 2 - 175;

        int overlayId = addEntityExtra<SpriteEntity>([](Entity* entity)
        {
            entity->addComponent("animation", new AnimationComponent(255, 0, 300.f, [sprite = entity->getComponent<TextureComponent>("texture")](float newValue) { sprite->setColor(sprite->getColor().WithAlpha(newValue)); }, nullptr, false));
        }, "textures/rectangle.png", 0, 0, Color{ 0, 0, 0, 0 }, wW, wH, 9999);

        auto overlayEntity = getEntity(overlayId);
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
        auto buttonLongTexture = "textures/button_white_long.png";
        auto buttonColor = Color{ 35, 65, 112 };
        auto buttonTextColor = Color::White();
        auto buttonSize = Size{ 150 * 2, 50 * 2 };
        auto buttonDeleteSize = Size{ 150 * 2, 50 };

        float offset_max = 150.f;
        float offset = offset_max;

        

        addEntity<SpriteEntity>("textures/choose_profile.png", (wW / 2) - 192, wH - 750, Color::White(), -1, -1);

        FileParser parser;
        map<string, int> p1_resources = parser.resourcesContent(Player::playerOne());
        map<string, int> p2_resources = parser.resourcesContent(Player::playerTwo());
        map<string, int> p3_resources = parser.resourcesContent(Player::playerThree());

        float scale = 1.5f;
        int font = static_cast<int>(20.f / scale);
        float rY = wH - 582.f;
        float rX = wW / scale - 240.f;
        float rIncr = 91.f / scale;

        std::string text;
        Size use_size;
        std::string use_texture;

        if (!p1_resources.empty()) {
            addEntity<SpriteEntity>("textures/resources-hud.png", rX - 40.f, rY - (401.f / scale) / 2.f + 55.f, Color::White(), 401 / scale, 169 / scale, 100u);
            addEntity<ResourceUIEntity>(rX + (rIncr * 0), rY, Color::White(), "uranium", p1_resources["uranium"], font);
            addEntity<ResourceUIEntity>(rX + (rIncr * 1), rY, Color::White(), "diamond", p1_resources["diamond"], font);
            addEntity<ResourceUIEntity>(rX + (rIncr * 2), rY, Color::White(), "metal", p1_resources["metal"], font);
            addEntity<ResourceUIEntity>(rX + (rIncr * 3), rY, Color::White(), "anti-matter", p1_resources["anti-matter"], font);

            text = "Select 'biem'";
            offset = offset_max;

            addEntity<ButtonUIEntity>((wW / 2) - (buttonSize.width / 2) - offset, wH - 595, Color{ 135, 25, 25 }, buttonTextColor, buttonDeleteSize, "Delete", buttonLongTexture,
                [this](StateManager* manager)
            {
                FileHandler fh{ "" };
                fh.remove((Player::playerOne().resourceLocation()));
                fh.remove((Player::playerOne().saveLocation()));
                manager->navigateTo<ProfileScene>();
            });

            use_size = buttonDeleteSize;
            use_texture = buttonLongTexture;
        }
        else {
            text = "Start profile 'Biem'";
            offset = 0.f;

            use_size = buttonSize;
            use_texture = buttonTexture;
        }

        addEntity<ButtonUIEntity>((wW / 2) - (buttonSize.width / 2) - offset, wH - 650, buttonColor, buttonTextColor, use_size, text, use_texture,
            [this](StateManager* manager)
        {
            Player::current().setName(Player::playerOneName());
            manager->navigateTo<MenuScene>();;
        });

        rY += 150.f;
        if (!p2_resources.empty()) {
            addEntity<SpriteEntity>("textures/resources-hud.png", rX - 40.f, rY - (401.f / scale) / 2.f + 55.f, Color::White(), 401 / scale, 169 / scale, 100u);
            addEntity<ResourceUIEntity>(rX + (rIncr * 0), rY, Color::White(), "uranium", p2_resources["uranium"], font);
            addEntity<ResourceUIEntity>(rX + (rIncr * 1), rY, Color::White(), "diamond", p2_resources["diamond"], font);
            addEntity<ResourceUIEntity>(rX + (rIncr * 2), rY, Color::White(), "metal", p2_resources["metal"], font);
            addEntity<ResourceUIEntity>(rX + (rIncr * 3), rY, Color::White(), "anti-matter", p2_resources["anti-matter"], font);

            text = "Select 'Mummy'";
            offset = offset_max;

            addEntity<ButtonUIEntity>((wW / 2) - (buttonSize.width / 2) - offset, wH - 445, Color{ 135, 25, 25 }, buttonTextColor, buttonDeleteSize, "Delete", buttonLongTexture,
                [this](StateManager* manager)
            {
                FileHandler fh{ "" };
                fh.remove((Player::playerTwo().resourceLocation()));
                fh.remove((Player::playerTwo().saveLocation()));
                manager->navigateTo<ProfileScene>();
            });

            use_size = buttonDeleteSize;
            use_texture = buttonLongTexture;
        }
        else {
            text = "Start profile 'Mummy'";
            offset = 0.f;

            use_size = buttonSize;
            use_texture = buttonTexture;
        }

        addEntity<ButtonUIEntity>((wW / 2) - (buttonSize.width / 2) - offset, wH - 500, buttonColor, buttonTextColor, use_size, text, use_texture,
            [this](StateManager* manager)
        {
            Player::current().setName(Player::playerTwoName());
            manager->navigateTo<MenuScene>();;
        });

        rY += 150.f;
        if (!p3_resources.empty()) {
            addEntity<SpriteEntity>("textures/resources-hud.png", rX - 40.f, rY - (401.f / scale) / 2.f + 55.f, Color::White(), 401 / scale, 169 / scale, 100u);
            addEntity<ResourceUIEntity>(rX + (rIncr * 0), rY, Color::White(), "uranium", p3_resources["uranium"], font);
            addEntity<ResourceUIEntity>(rX + (rIncr * 1), rY, Color::White(), "diamond", p3_resources["diamond"], font);
            addEntity<ResourceUIEntity>(rX + (rIncr * 2), rY, Color::White(), "metal", p3_resources["metal"], font);
            addEntity<ResourceUIEntity>(rX + (rIncr * 3), rY, Color::White(), "anti-matter", p3_resources["anti-matter"], font);

            text = "Select 'Snowman'";
            offset = offset_max;

            addEntity<ButtonUIEntity>((wW / 2) - (buttonSize.width / 2) - offset, wH - 295, Color{ 135, 25, 25 }, buttonTextColor, buttonDeleteSize, "Delete", buttonLongTexture,
                [this](StateManager* manager)
            {
                FileHandler fh{""};
                fh.remove((Player::playerThree().resourceLocation()));
                fh.remove((Player::playerThree().saveLocation()));

                manager->navigateTo<ProfileScene>();
            });

            use_size = buttonDeleteSize;
            use_texture = buttonLongTexture;
        }
        else {
            text = "Start profile 'Snowman'";
            offset = 0.f;

            use_size = buttonSize;
            use_texture = buttonTexture;
        }

        addEntity<ButtonUIEntity>((wW / 2) - (buttonSize.width / 2) - offset, wH - 350, buttonColor, buttonTextColor, use_size, text, use_texture,
            [this](StateManager* manager)
        {
            Player::current().setName(Player::playerThreeName());
            manager->navigateTo<MenuScene>();
        });

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
