#include "..\..\stdafx.h"
#include "bmSystemManager.h"
#include "..\systems\bmRenderSystem.h"

bmSystemManager::bmSystemManager()
{

}

bmSystemManager::~bmSystemManager()
{
    for (auto it = systems.begin(); it != systems.end(); ++it)
    {
        delete (*it);
    }
}

void bmSystemManager::preUpdate()
{
    for (auto* s : systems) {
        s->before();
    }
}

void bmSystemManager::preUpdate(const float deltaTime)
{
    for (auto* s : systems) {
        s->before(deltaTime);
    }
}

void bmSystemManager::postUpdate()
{
    for (auto* s : systems) {
        s->after();
    }
}

void bmSystemManager::postUpdate(const float deltaTime)
{
    for (auto* s : systems) {
        s->after(deltaTime);
    }
}


void bmSystemManager::acceptForUpdate(const bmEntity & entity)
{
    for (auto* s : systems) {
        s->update(entity);
    }
}

void bmSystemManager::acceptForUpdate(const bmEntity & entity, const float deltaTime)
{
    for (auto* s : systems) {
        s->update(entity, deltaTime);
    }
}

void bmSystemManager::addSystem(bmSystem * system)
{
    systems.push_back(system);
}

void bmSystemManager::onSceneSwitch()
{
    for (auto* s : systems) {
        s->onSceneSwitch();
    }
}
