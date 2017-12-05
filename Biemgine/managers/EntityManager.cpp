#include "stdafx.h"
#include "EntityManager.h"

#include <chrono>
#include <algorithm>

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
        manager->preUpdate();

        for (Entity * e : entities) {

            if (canUpdate(*e))
                manager->acceptForUpdate(*e);
        }

        manager->postUpdate();
    }

    inline void EntityManager::updateEntities(std::shared_ptr<SystemManager> manager, const float deltaTime)
    {
        //auto start = std::chrono::high_resolution_clock::now();

        //manager->preUpdate(deltaTime);

        for (Entity * e : entities) {

            if (canUpdate(*e)) {
                manager->acceptForUpdate(*e, deltaTime);
            }
        }

        manager->postUpdate(deltaTime);

        /*auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> diff = end - start;*/

        //printf("Timed Update took %f s\n", diff.count());
    }

    inline EntityManager::const_iterator EntityManager::begin() const {
        return entities.begin();
    }

    inline EntityManager::const_iterator EntityManager::end() const {
        return entities.end();
    }

    inline EntityManager::iterator EntityManager::begin()
    {
        return entities.begin();
    }

    inline EntityManager::iterator EntityManager::end()
    {
        return entities.end();
    }

    EntityManager::entity_ptr EntityManager::getEntity(int id) const
    {
        auto result = std::find_if(entities.begin(), entities.end(), [id](EntityManager::entity_ptr e) { return e->getId() == id; });

        if (result != entities.end()) {
            return (*result);
        }

        return nullptr;
    }

    EntityManager::entity_ptr EntityManager::getEntity(string tag) const
    {
        auto result = std::find_if(entities.begin(), entities.end(), [tag](EntityManager::entity_ptr e) { return e->getTag() == tag; });

        if (result != entities.end()) {
            return (*result);
        }

        return nullptr;
    }

    EntityManager::storage::const_iterator EntityManager::inView() const
    {
        return storage::const_iterator();
    }

    bool EntityManager::canUpdate(const Entity & e)
    {
        if (!e.isAlive()) return false;


        if (camera != nullptr &&
            e.hasComponent("position") &&
            !e.hasComponent("camera") &&
            !e.hasComponent("ui") ) {

            auto pc = e.getComponent<PositionComponent>("position");

            float dX = camera.get()->getOriginX();
            float dY = camera.get()->getOriginY();
            int wW = camera.get()->getWindowWidth();
            int wH = camera.get()->getWindowHeight();

            if (pc.get()->getOriginX() < dX - wW) return false;
            if (pc.get()->getOriginX() > dX + wW) return false;
            if (pc.get()->getOriginY() < dY - wH) return false;
            if (pc.get()->getOriginY() > dY + wH) return false;

        }

        return true;
    }
}
