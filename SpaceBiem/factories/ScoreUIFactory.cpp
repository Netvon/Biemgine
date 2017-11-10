#include "stdafx.h"
#include "ScoreUIFactory.h"

#include <windows.h>
#include <Lmcons.h>

#include "..\entities\ScoreUIEntity.h"
#include "..\components\ScoreComponent.h"

namespace spacebiem
{
    vector<Entity*> ScoreUIFactory::sceneStart(int windowW, int windowH)
    {
        vector<Entity*> entities;

        int w = 50;
        int x = windowW / 2 - w;
        int y = 200;
        int dY = 30;

        FileHandler fh;

        for (int i = 0; i < 15; i++) {
            if (y + (dY * 4) > windowH) break;
            entities.push_back(new ScoreUIEntity(x, y, fh.scoresContent().at(i).second, fh.scoresContent().at(i).first));
            y += dY;
        }

        return entities;
    }

    void ScoreUIFactory::sceneEnd(std::vector<Entity*> entities)
    {
        FileHandler fh;

        TCHAR user[UNLEN + 1];
        DWORD size = UNLEN + 1;
        string name = "Mr. NoName";

        if (GetUserName((TCHAR*)user, &size)) {
            wstring test(&user[0]);
            string stringName(test.begin(), test.end());
            name = stringName;
        }

        for (Entity* e : entities) {
            if (e->hasComponent("score") && !e->hasComponent("ui")) {
                auto sc = e->getComponent<ScoreComponent*>("score");
                fh.writeScore(name, sc->getScore());
            }
        }
    }
}
