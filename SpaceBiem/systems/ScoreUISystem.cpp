#include "stdafx.h"
#include <windows.h>
#include <Lmcons.h>
#include "ScoreUISystem.h"



namespace spacebiem
{
    void ScoreUISystem::onAddEntity(Entity & entity)
    {
        if (!entity.hasComponent("score")) return;

        auto sc = entity.getComponent<ScoreComponent>("score");

        if (!entity.hasComponent("ui"))
        {
            PlayerEntry playerEntry;
            playerEntry.entity = &entity;
            playerEntry.scoreComponent = sc;

            playerEntries.push_back(std::move(playerEntry));
        }
        else
        {
            ScoreUIEntry scoreUIEntry;
            scoreUIEntry.entity = &entity;
            scoreUIEntry.scoreComponent = sc;
            scoreUIEntry.textComponent = entity.getComponent<TextComponent>("text");

            scoreUIEntries.push_back(std::move(scoreUIEntry));
        }
    }

    void ScoreUISystem::update()
    {
        if (playerEntries.empty())
        {
            for (ScoreUIEntry score : scoreUIEntries)
            {
                TCHAR user[UNLEN + 1];
                DWORD size = UNLEN + 1;
                string name = "Mr. NoName";

                if (GetUserName((TCHAR*)user, &size))
                {
                    wstring test(&user[0]);
                    string stringName(test.begin(), test.end());
                    name = stringName;
                }

                Color highlightColor{255, 255, 255};

                if (name == score.scoreComponent->getName())
                {
                    highlightColor = {232, 228, 41};
                }

                score.textComponent->setText(score.scoreComponent->getName() + ": " + std::to_string((int)score.scoreComponent->getScore()), highlightColor);
            }
        }
        else
        {
            for (PlayerEntry player : playerEntries)
            {
                for (ScoreUIEntry score : scoreUIEntries)
                {
                    score.textComponent->setText(player.scoreComponent->getName() + ": " + std::to_string((int)player.scoreComponent->getScore()), {255, 255, 255});
                }
            }
        }
        
    }

    void ScoreUISystem::update(const Entity & entity)
    {
    //    if (!entity.hasComponent("score")) return;

    //    auto oc = entity.getComponent<ScoreComponent>("score");

    //    if (!entity.hasComponent("ui")) {
    //        if (scoreMap.find(oc) == scoreMap.end()) {
    //            scoreMap[oc] = false;
    //        }
    //        return;
    //    }

    //    if (!entity.hasComponent("position")) return;

    //    auto pc = entity.getComponent<PositionComponent>("position");
    //    auto uc = entity.getComponent<UIComponent>("ui");

    //    // If the UI doesn't have the component which to draw, pick one from the map.
    //    auto oRef = uc->getComponentReference<ScoreComponent>();

    //    if (oRef == nullptr) {
    //        for (auto x : scoreMap)
    //        {
    //            if (!x.second) {
    //                uc->setComponentReference(x.first);
    //                oRef = x.first;
    //                break;
    //            }
    //        }

    //        if (oRef != nullptr) scoreMap[oRef] = true;
    //        else oRef = oc;
    //    }

    //    TCHAR user[UNLEN + 1];
    //    DWORD size = UNLEN + 1;
    //    string name = "Mr. NoName";

    //    if (GetUserName((TCHAR*)user, &size)) {
    //        wstring test(&user[0]);
    //        string stringName(test.begin(), test.end());
    //        name = stringName;
    //    }

    //    auto tx = entity.getComponent<TextComponent>("text");

    //    Color highlightColor { 255, 255, 255 };

    //    if (name == oRef->getName()) {
    //        highlightColor = { 232, 228, 41 };
    //    }

    //    tx->setText(oRef->getName() + ": " + std::to_string((int)oRef->getScore()), highlightColor);

    }
}
