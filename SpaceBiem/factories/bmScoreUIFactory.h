#pragma once

#include "stdafx.h"

#include "bmEntityFactory.h"
#include "bmFileHandler.h"

using namespace biemgine;

class bmScoreUIFactory :
    public bmEntityFactory
{
public:

    ~bmScoreUIFactory() { };
    vector<bmEntity*> sceneStart(int windowW, int windowH) override;
    void sceneEnd(vector<bmEntity*> entities) override;
};

