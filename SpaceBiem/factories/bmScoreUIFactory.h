#pragma once

#include "stdafx.h"

#include "bmEntityFactory.h"
#include "..\bmFileHandler.h"
#include <vector>

using namespace biemgine;

class bmScoreUIFactory :
    public bmEntityFactory
{
public:

    ~bmScoreUIFactory() { };
    vector<bmEntity*> sceneStart(int windowW, int windowH) override;
    void sceneEnd(std::vector<bmEntity*> entities) override;
};

