#include "stdafx.h"
#include "EntityManager.h"

#include <chrono>

namespace biemgine
{
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

        for (Entity * e : entities) {

            if (canUpdate(*e))
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

        for (Entity * e : entities) {

            

            if (canUpdate(*e))
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

    bool EntityManager::canUpdate(const Entity & e)
    {
        if (!e.isAlive()) return false;

        if (camera != nullptr && e.isCheckable() ) {

            auto pc = e.getComponent<PositionComponent>("position");

            float dX = camera.get()->getOriginX();
            float dY = camera.get()->getOriginY();
            int wW = camera.get()->getWindowWidth() / 2;
            int wH = camera.get()->getWindowHeight() / 2;

            if (e.minX + pc.get()->getOriginX() > dX + wW) return false;
            if (e.maxX + pc.get()->getOriginX() < dX - wW) return false;
            if (e.minY + pc.get()->getOriginY() > dY + wH) return false;
            if (e.maxY + pc.get()->getOriginY() < dY - wH) return false;
        }

        return true;
    }
}
