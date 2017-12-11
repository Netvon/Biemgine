#include "stdafx.h"
#include "HighScoreScene.h"
#include "MenuScene.h"
#include "..\entities\PlanetEarthEntity.h"
#include "..\entities\PlanetMoonEntity.h"
#include "..\entities\ButtonUIEntity.h"
#include "..\entities\ScoreUIEntity.h"
#include "..\factories\ScoreUIFactory.h"
#include "..\systems\ScoreUISystem.h"

using biemgine::Size;
using biemgine::SpriteEntity;

namespace spacebiem
{
    void onHighScoreButtonEntered(StateManager* e)
    {
        e->getAudioDevice().playSoundEffect("audio/switch.mp3", 0, -1, 128);
    }

    void BackButtonClicked(StateManager* e)
    {
        e->getAudioDevice().playSoundEffect("audio/idroid.mp3", 0, -1, 128);
        e->navigateTo<MenuScene>();
    }

    void HighScoreScene::created() {
        enableRendering();
        enableUI();
        enableScripts();

        addSystem<ScoreUISystem>();

        int wW = getTransitionManager().getWindowWidth();
        int wH = getTransitionManager().getWindowHeight();
        float planetWidth = 500;
        float planetHeight = 500;
        int w = 50;
        int x = wW / 2 - w;

        addEntity<SpriteEntity>("textures/highscores.png", static_cast<float>(x - 50.f), 100.f, Color::White(), -1, -1, 100u);

        ScoreUIFactory sf;
        sf.sceneStart(wW, wH, getEntityManager());

        if (lastScore >= 0) {
            addEntity<ScoreUIEntity>(x, 670, lastScore, "Last score");
        }

        addEntity<PlanetEarthEntity>(-250.f, static_cast<float>(wH - 250), Color({71, 166, 245, 255}), planetWidth, planetHeight, 0, 10.f);
        addEntity<PlanetMoonEntity>(static_cast<float>(wW - 250), static_cast<float>(wH - 250), Color::White(), planetWidth, planetHeight, 0);
        
        addEntity<ButtonUIEntity>(x - 25, 750, Color{ 35, 65, 112 }, Color::White(), Size{ 150, 50 }, "Menu", "textures/button_white.png", BackButtonClicked, onHighScoreButtonEntered);
    }

    void HighScoreScene::input()
    {
        if (im.isKeyDown("Q")) {
            signalQuit();
        }

        if (im.isKeyDown("Backspace")) {
            getTransitionManager().navigateTo<MenuScene>();
        }
    }

    void HighScoreScene::update()
    {
        updateEntities();
    }

    void HighScoreScene::render(const float deltaTime)
    {
        getTransitionManager().drawBackground("textures/space.png");
        updateEntities(deltaTime);
    }
}
