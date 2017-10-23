#pragma once
#include "bmSystem.h"
#include "bmEntity.h"
#include "bmPhysicsComponent.h"
#include "bmAffectedByGravityComponent.h"

#include <vector>

using namespace std;
class bmGravitySystem :
	public bmSystem
{
public:
    void update(const bmEntity& entity) override;
    void after() override;

    void applyForce(glm::vec2 centerOfGravity, glm::vec2 centerOfSatellite, bmPhysicsComponent * satPhysics, bmAffectedByGravityComponent* affected);

    void onSceneSwitch() override {};
    
private:
    vector<const bmEntity*> gravityPoints;
    vector<const bmEntity*> satellites;
};

