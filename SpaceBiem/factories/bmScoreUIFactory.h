#pragma once
#include "bmEntity.h"
#include "bmScoreUIEntity.h"
#include "bmEntityFactory.h"
#include "bmFileHandler.h"
#include "bmScoreComponent.h"

class bmScoreUIFactory : public bmEntityFactory
{
public:

    ~bmScoreUIFactory() { };
    vector<bmEntity*> sceneStart(int windowW, int windowH) override;
    void sceneEnd(vector<bmEntity*> entities) override;
};

