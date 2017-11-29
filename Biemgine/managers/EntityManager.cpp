#include "stdafx.h"
#include "EntityManager.h"

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

    void EntityManager::updateEntities(std::shared_ptr<SystemManager> manager)
    {
        manager->preUpdate();

        for (Entity * e : entities) {

            if (canUpdate(*e)) manager->acceptForUpdate(*e);
        }

        manager->postUpdate();
    }

    void EntityManager::updateEntities(std::shared_ptr<SystemManager> manager, const float deltaTime)
    {
        manager->preUpdate(deltaTime);

        for (Entity * e : entities) {

            if(canUpdate(*e)) manager->acceptForUpdate(*e, deltaTime);
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
