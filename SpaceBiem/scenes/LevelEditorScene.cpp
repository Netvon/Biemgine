#include "stdafx.h"

#include "LevelEditorScene.h"
#include "MenuScene.h"
#include "LevelScene.h"
#include "LevelLoadScene.h"

#include "..\entities\ButtonUIEntity.h"

#include "../entities/PlanetEarthEntity.h"
#include "../entities/PlanetMoonEntity.h"
#include "../entities/PlanetSandEntity.h"
#include "../entities/PlanetToxicEntity.h"
#include "../entities/PlanetIceEntity.h"
#include "../entities/PlanetLavaEntity.h"

#include "../entities/MummieAIEntity.h"
#include "../entities/SnowmanAIEntity.h"

#include "../entities/ResourceEntity.h"
#include "../components/ResourceBonusComponent.h"

#include "../entities/PlayerEntity.h"

#include "../entities/CameraEntity.h"

#include "../systems/DragDropSystem.h"
#include "../systems/GravitySystem.h"

#include "../factories/UniverseBuilder.h"

#include "..\globals\Fonts.h"
#include "../globals/Colors.h"

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
        enableCamera();

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
        addEntity<SpriteEntity>("textures/rectangle.png", wW - menuSize, 0, Color{ 0, 0, 0, 150 }, menuSize, wH, 0u, "entity_menu");

        UniverseBuilder uB;
        uB.build(getEntityManager(), false, slotFileName, false);

        for (auto it = getEntityManager()->begin(); it != getEntityManager()->end(); it++) {
            (*it)->setTag((*it)->getTag() + "_placed");
        }

        fillMenuEntitySpace();


        addEntity<ButtonUIEntity>((wW) - (buttonSize.width) - 20, wH - buttonSize.height - 20, buttonColor, buttonTextColor, buttonSize, "Back to slots", buttonTexture,
            [this](StateManager* manager)
        {
            manager->navigateTo<LevelLoadScene>();
        });

        addEntity<SpriteEntity>("textures/kliko.png", wW - menuSize + 30, wH - buttonSize.height - 50, Color::White(), 80, 80, 200u, "kliko");

        addEntity<CameraEntity>(wW/2, wH/2, "_placed");

    }


    void LevelEditorScene::fillMenuEntitySpace() {

        int wW = getTransitionManager().getWindowWidth();
        int wH = getTransitionManager().getWindowHeight();

        int menuSize = 400;

        int column1X = 1600;
        int column15X = 1700;
        int column2X = 1800;
        int row1Y = 100;
        int row2Y = 300;
        int row3Y = 500;
        int row4Y = 700;
        int planetWidth = 80;

        int resourceWidth = 40;
        int rColumn1 = 1600;
        int rColumn2 = 1680;
        int rColumn3 = 1760;
        int rColumn4 = 1840;

        int row5Y = 800;
        int aiWidth = 70;
        int aiHeight = 70;


        bool earthGone = true;
        bool moonGone = true;
        bool sandGone = true;
        bool toxicGone = true;
        bool iceGone = true;
        bool lavaGone = true;

        bool metalGone = true;
        bool diamondGone = true;
        bool uraniumGone = true;
        bool antimatterGone = true;

        bool playerGone = true;
        bool mummieGone = true;
        bool snowmanGone = true;

        auto em = getEntityManager();
        for (auto it = em->begin(); it != em->end(); it++) {
            if ((*it)->getTag() == "earth") earthGone = false;
            if ((*it)->getTag() == "moon") moonGone = false;
            if ((*it)->getTag() == "sand") sandGone = false;
            if ((*it)->getTag() == "toxic") toxicGone = false;
            if ((*it)->getTag() == "ice") iceGone = false;
            if ((*it)->getTag() == "lava") lavaGone = false;
            if ((*it)->getTag() == "resource") {
                string name = (*it)->getComponent<ResourceBonusComponent>("resourcebonus")->getName();
                if (name == "metal") metalGone = false;
                if (name == "diamond") diamondGone = false;
                if (name == "uranium") uraniumGone = false;
                if (name == "anti-matter") antimatterGone = false;
            }
            if ((*it)->getTag() == "ai") {
                string name = (*it)->getComponent<AIComponent>("ai")->getName();
                if (name == "mummie") mummieGone = false;
                if (name == "snowman") snowmanGone = false;
            }
            if ((*it)->getTag() == "player_placed" || (*it)->getTag() == "player") playerGone = false;
        }

        if (earthGone) addEntity<PlanetEarthEntity>(column1X, row1Y, Colors::EarthAtmosphere(), planetWidth, planetWidth, 0, 10.f, nameGenerator.getName());
        if (moonGone) addEntity<PlanetMoonEntity>(column2X, row1Y, Colors::MoonAtmosphere(), planetWidth, planetWidth, 10.f, nameGenerator.getName());
        if (sandGone) addEntity<PlanetSandEntity>(column1X, row2Y, Colors::SandAtmosphere(), planetWidth, planetWidth, 0, 10.f, nameGenerator.getName());
        if (toxicGone) addEntity<PlanetToxicEntity>(column2X, row2Y, Colors::ToxicAtmosphere(), planetWidth, planetWidth, 0, 10.f, nameGenerator.getName());
        if (iceGone) addEntity<PlanetIceEntity>(column1X, row3Y, Colors::IceAtmosphere(), planetWidth, planetWidth, 0, 10.f, nameGenerator.getName());
        if (lavaGone) addEntity<PlanetLavaEntity>(column2X, row3Y, Colors::LavaAtmosphere(), planetWidth, planetWidth, 0, 10.f, nameGenerator.getName());

        if (metalGone) addEntity<ResourceEntity>(rColumn1, row4Y, Color::White(), resourceWidth, resourceWidth, "metal");
        if (diamondGone) addEntity<ResourceEntity>(rColumn2, row4Y, Color::White(), resourceWidth, resourceWidth, "diamond");
        if (uraniumGone) addEntity<ResourceEntity>(rColumn3, row4Y, Color::White(), resourceWidth, resourceWidth, "uranium");
        if (antimatterGone) addEntity<ResourceEntity>(rColumn4, row4Y, Color::White(), resourceWidth, resourceWidth, "anti-matter");

        if (playerGone) addEntity<PlayerEntity>(column1X, row5Y, Color::White(), aiWidth/2, aiHeight, 1.0f, false);
        if (mummieGone) addEntity<MummieAIEntity>(column15X, row5Y, Color::White(), aiWidth, aiHeight);
        if (snowmanGone) addEntity<SnowmanAIEntity>(column2X, row5Y, Color::White(), aiWidth, aiHeight);

    }

    void LevelEditorScene::end()
    {
        SaveBlobFactory saveBlobFactory;
        vector<string> saveBlob = saveBlobFactory.createFromEntities(getEntityManager(), "_placed");

        FileHandler fileHandler(slotFileName, true);

        for (auto it = saveBlob.begin(); it != saveBlob.end(); it++) {
            fileHandler.writeLine(*it);
        }
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
        fillMenuEntitySpace();
    }

    void LevelEditorScene::render(const float deltaTime)
    {
        getTransitionManager().drawBackground("textures/space.png");
        updateEntities(deltaTime);
    }
}
