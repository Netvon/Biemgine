#include "stdafx.h"
#include "EntityManager.h"

#include <chrono>

namespace biemgine
{
    EntityManager::EntityManager(std::shared_ptr<SystemManager> manager) : systemManager(manager)
    {}

    EntityManager::~EntityManager()
    {
        for (auto it = entities.begin(); it != entities.end(); ++it)
        {
            delete (*it);
        }

        entities.clear();
    }

    int EntityManager::addEntity(Entity* entity)
    {
        entities.push_back(entity);
        if (!camera && entity->hasComponent("camera")) {
            camera = entity->getComponent<CameraComponent>("camera");
        }
        return entity->getId();
    }

    inline void EntityManager::updateEntities(std::shared_ptr<SystemManager> manager)
    {
        //std::cout << std::endl;

        manager->preUpdate();
        manager->acceptForUpdate();

        for (Entity * e : entities) {

            if (e->getIsOnScreen())
            {
                //auto start = std::chrono::high_resolution_clock::now();
                manager->acceptForUpdate(*e);

                //auto end = std::chrono::high_resolution_clock::now();
               // std::chrono::duration<double> diff = end - start;

                //std::cout << std::fixed;
                //std::cout << typeid(*e).name() << "time: " << diff.count() << std::endl;
            }
                
        }

        //std::cout << std::endl;

        manager->postUpdate();
    }

    inline void EntityManager::updateEntities(std::shared_ptr<SystemManager> manager, const float deltaTime)
    {
        manager->preUpdate(deltaTime);
        manager->acceptForUpdate(deltaTime);

        for (Entity * e : entities) {

            if (e->getIsOnScreen())
            {
                manager->acceptForUpdate(*e, deltaTime); 
            }
        }

        manager->postUpdate(deltaTime); 
    }

    Entity* EntityManager::getEntity(int id) const
    {
        for (auto entity = entities.begin(); entity != entities.end(); ++entity)
        {
            if ((*entity)->getId() == id) return (*entity);
        }

        return nullptr;
    }

    Entity * EntityManager::getEntity(string tag) const
    {
        for (auto entity = entities.begin(); entity != entities.end(); ++entity)
        {
            if ((*entity)->getTag() == tag) return (*entity);
        }

        return nullptr;
    }
}
