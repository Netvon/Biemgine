#pragma once
#include "bmSystem.h"
#include "bmEntity.h"

#include <vector>

class bmSystemManager 
{
public:
	
	bmSystemManager();

	~bmSystemManager();

    void preUpdate();
    void preUpdate(const float deltaTime);

    void postUpdate();
    void postUpdate(const float deltaTime);

    void acceptForUpdate(const bmEntity& entity);
    void acceptForUpdate(const bmEntity& entity, const float deltaTime);

	void addSystem(bmSystem* system);

	void onSceneSwitch();
private:
	std::vector<bmSystem*> systems;

};

