#include "stdafx.h"
#include "SystemManager.h"
#include "..\systems\RenderSystem.h"

namespace biemgine
{
    SystemManager::SystemManager() {}

    SystemManager::~SystemManager()
    {
        for (auto it = systems.begin(); it != systems.end(); ++it)
        {
            delete (*it);
        }
    }

    inline void SystemManager::preUpdate()
    {
        for (auto* s : systems) {
            //s->nextUpdate();
            /*if(!s->hasTimedOut())*/ s->before();
        }
    }

    /*void SystemManager::preUpdate(const float deltaTime)
    {
        for (auto* s : systems) {
            s->before(deltaTime);
        }
    }*/

    inline void SystemManager::postUpdate()
    {
        for (auto* s : systems) {
            /*if (!s->hasTimedOut())*/ s->after();
        }
    }

    inline void SystemManager::postUpdate(const float deltaTime)
    {
        for (auto* s : systems) {
            s->after(deltaTime);
        }
    }

    inline void SystemManager::acceptForUpdate(const Entity & entity)
    {
        for (auto* s : systems) {
            if (!s->hasTimedOut()) s->update(entity);
        }
    }

    inline void SystemManager::acceptForUpdate(const Entity & entity, const float deltaTime)
    {
        for (auto* s : systems) {
            s->update(entity, deltaTime);
        }
    }

    void SystemManager::updateSystems(float dt, bool usedt)
    {
        for (auto& entry : update_map) {
            auto system = entry.first;

            /*if (system->hasTimedOut())
                continue;*/

            for (auto entity : entry.second) {
                if (usedt)
                    system->update(*entity, dt);
                else
                    system->update(*entity);
            }
        }
    }

    void SystemManager::addSystem(System * system)
    {
        systems.push_back(system);
    }

    void SystemManager::onSceneSwitch()
    {
        for (auto* s : systems) {
            s->onSceneSwitch();
        }
    }
}
