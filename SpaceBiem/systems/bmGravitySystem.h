#pragma once

#include "Biemgine.h"
#include <vector>

using namespace std;
using namespace biemgine;

class bmGravitySystem :
    public bmSystem
{
public:
    void update(const bmEntity& entity) override;
    void after() override;

    void applyForce(bmVector centerOfGravity, bmVector centerOfSatellite, bmPhysicsComponent * satPhysics, bmAffectedByGravityComponent* affected);

    void onSceneSwitch() override {};
    
private:
    vector<const bmEntity*> gravityPoints;
    vector<const bmEntity*> satellites;
};

