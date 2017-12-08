#include "stdafx.h"
#include "CreditsScene.h"
#include "MenuScene.h"
#include "..\entities\ButtonUIEntity.h"

using biemgine::Size;
using biemgine::SpriteEntity;

namespace spacebiem
{
    void BackButtonClicked(StateManager* e)
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
        int x = wW / 2 - w;

        addEntity<SpriteEntity>("textures/highscores.png", static_cast<float>(x - 50.f), 100.f, Color::White(), -1, -1, 100u);
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
