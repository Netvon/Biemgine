#include "stdafx.h"
#include "ScoreUIFactory.h"

#include <windows.h>
#include <Lmcons.h>

#include "..\entities\ScoreUIEntity.h"
#include "..\components\ScoreComponent.h"

namespace spacebiem
{
    void ScoreUIFactory::sceneStart(int windowW, int windowH, shared_ptr<EntityManager> entityManager)
    {
        int w = 50;
        int x = windowW / 2 - w;
        int y = 200;
        int dY = 30;

        FileParser fh;

        int counter = 0;

        for (auto const& score : fh.scoresContent()) {
            if (counter == 15) break;

            if (y + (dY * 4) > windowH) break;

            entityManager->addEntity<ScoreUIEntity>(x, y, score.second, score.first);

            y += dY;
            counter++;
        }
    }

    void ScoreUIFactory::sceneEnd(shared_ptr<EntityManager> entityManager)
    {
        FileParser fh;

        TCHAR user[UNLEN + 1];
        DWORD size = UNLEN + 1;
        string name = "Mr. NoName";

        if (GetUserName((TCHAR*)user, &size)) {
            wstring test(&user[0]);
            string stringName(test.begin(), test.end());
            name = stringName;
        }

        for (auto it = entityManager->begin(); it != entityManager->end(); it++) {
            auto e = (*it);

            if (e->hasComponent("score") && !e->hasComponent("ui")) {
                auto sc = e->getComponent<ScoreComponent*>("score");
                fh.writeScore(name, sc->getScore());
            }
        }
    }
}
