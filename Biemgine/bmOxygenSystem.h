#pragma once

#include "bmSystem.h"
#include "bmOxygenComponent.h"
#include "bmAtmosphereComponent.h"
#include "bmPositionComponent.h"

class bmOxygenSystem : public bmSystem
{
public:

    bmOxygenSystem() {};
    ~bmOxygenSystem() {};

    void before() override;
    void update(const bmEntity& entity) override;
    void after() override;

    void onSceneSwitch() override;


private:
    vector<bmAtmosphereComponent*> atmospheres;

};

