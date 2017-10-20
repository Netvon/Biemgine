#pragma once
#include "bmSystem.h"
#include "bmEntity.h"

#include <vector>
using namespace std;
class bmGravitySystem :
	public bmSystem
{
public:
    void update(const bmEntity& entity) override;
    void after() override;

    void onSceneSwitch() override {};

private:
    vector<const bmEntity*> gravityPoints;
    vector<const bmEntity*> satellites;
};

