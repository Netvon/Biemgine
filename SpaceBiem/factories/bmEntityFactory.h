#pragma once

#include "stdafx.h"

using namespace biemgine;

class bmEntityFactory
{
public:
    virtual ~bmEntityFactory() { };
    virtual vector<bmEntity*> sceneStart(int windowWidth, int windowH) =0;
    virtual void sceneEnd(vector<bmEntity*> entities) =0;
};

