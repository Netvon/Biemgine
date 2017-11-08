#pragma once

#include "stdafx.h"
#include "Biemgine.h"
#include <vector>

using namespace biemgine;

class bmEntityFactory
{
public:
    virtual ~bmEntityFactory() { };
    virtual vector<bmEntity*> sceneStart(int windowWidth, int windowH) =0;
    virtual void sceneEnd(std::vector<bmEntity*> entities) =0;
};

