#pragma once
#include <systems\bmSystem.h>
#include <entities\bmEntity.h>
#include <components\bmPhysicsComponent.h>
#include <components\bmAffectedByGravityComponent.h>

#include <vector>


using namespace std;
using namespace biemgine;

class bmGravitySystem :
	public bmSystem
{
public:
    void update(const bmEntity& entity) override;
    void after() override;

    void applyForce(glm::vec2 centerOfGravity, glm::vec2 centerOfSatellite, components::bmPhysicsComponent * satPhysics, components::bmAffectedByGravityComponent* affected);

    void onSceneSwitch() override {};
    
private:
    vector<const bmEntity*> gravityPoints;
    vector<const bmEntity*> satellites;
};

