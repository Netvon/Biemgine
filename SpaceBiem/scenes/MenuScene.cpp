#include "MenuScene.h"

#include "..\factories\ScoreUIFactory.h"
#include "LevelScene.h"
#include "..\systems\ScoreUISystem.h"

using biemgine::SpriteEntity;

namespace spacebiem
{
    void MenuScene::created()
    {
        enableRendering();
        addSystem<ScoreUISystem>();

        int wW = getTransitionManager().getWindowWidth();
        int wH = getTransitionManager().getWindowHeight();
        int w = 50;
        int x = wW / 2 - w;

        addEntity(new SpriteEntity("textures/biemlogo.png", x, 100, { 255, 255, 255, 255 }, -1, -1 , 0u));

        ScoreUIFactory sf;
        for (auto e : sf.sceneStart(wW, wH)) {
            addEntity(e);
        }
    }

    void MenuScene::input()
    {
        if (im.isKeyDown("Q")) {
            signalQuit();
        }

        if (im.isKeyDown("Return")) {
            getTransitionManager().navigateTo<LevelScene>();
        }
    }

    void MenuScene::update()
    {
        updateEntities();
    }

    void MenuScene::render(const float deltaTime)
    {
        updateEntities(deltaTime);
    }
}
