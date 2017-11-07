#include "stdafx.h"
#include "bmScoreUIFactory.h"

#include <windows.h>
#include <Lmcons.h>

#include "..\entities\bmScoreUIEntity.h"
#include "..\components\bmScoreComponent.h"

vector<bmEntity*> bmScoreUIFactory::sceneStart(int windowW, int windowH)
{
    vector<bmEntity*> entities;

    int w = 50;
    int x = windowW / 2 - w;
    int y = 200;
    int dY = 30;

    bmFileHandler fh;

    for (auto const& score : fh.scoresContent()) {
        if (y + (dY * 4) > windowH) break;
        entities.push_back(new bmScoreUIEntity(x, y, score.second, score.first));
        y += dY;
    }

	return entities;
}

void bmScoreUIFactory::sceneEnd(vector<bmEntity*> entities)
{
    bmFileHandler fh;

    TCHAR user[UNLEN + 1];
    DWORD size = UNLEN + 1;
    string name = "Mr. NoName";

    if (GetUserName((TCHAR*)user, &size)) {
        wstring test(&user[0]);
        string stringName(test.begin(), test.end());
        name = stringName;
    }

    for (bmEntity* e : entities) {
        if (e->hasComponent("score") && !e->hasComponent("ui")) {
            auto sc = e->getComponent<bmScoreComponent*>("score");
            fh.writeScore(name, sc->getScore());
        }
    }
}
