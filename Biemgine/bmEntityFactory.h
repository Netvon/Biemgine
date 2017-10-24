#pragma once
#include "bmEntity.h"

class bmEntityFactory
{
public:

    virtual ~bmEntityFactory() { };
    virtual vector<bmEntity*> sceneStart(int windowWidth, int windowH) =0;
    virtual void sceneEnd(vector<bmEntity*> entities) =0;
    
protected:

};

