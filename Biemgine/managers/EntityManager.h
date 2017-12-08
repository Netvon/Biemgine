#pragma once
#include "stdafx.h"
#include "dlldef.h"
#include "..\entities\Entity.h"
#include "SystemManager.h"
#include "..\components\CameraComponent.h"
#include "..\components\PositionComponent.h"
#include <vector>
#include <memory>

namespace biemgine
{
    class BIEMGINE EntityManager
    {
    public:
        typedef Entity* entity_ptr;
        typedef std::vector<Entity*> storage;
        typedef std::map<std::string, std::size_t> tag_map;
        typedef std::shared_ptr<CameraComponent> camera_ptr;
        typedef std::string entity_tag;
        typedef storage::const_iterator const_iterator;
        typedef storage::iterator iterator;

        ~EntityManager();

        template<class TEntity, typename...TArgs>
        int addEntity(TArgs&&... arguments);
        int addEntity(Entity* entity);

        inline void updateEntities(std::shared_ptr<SystemManager> manager);
        inline void updateEntities(std::shared_ptr<SystemManager> manager, const float deltaTime);

        const_iterator begin() const;
        const_iterator end() const;

        iterator begin();
        iterator end();

        entity_ptr getEntity(int id) const;
        entity_ptr getEntity(string tag) const;

        storage::const_iterator inView() const;

    private:
        storage entities;
        tag_map tagMap;
        camera_ptr camera;

        bool canUpdate(const Entity& e);

    };

    template<class TEntity, typename ...TArgs>
    int EntityManager::addEntity(TArgs && ...arguments)
    {
        entities.emplace_back(new TEntity(std::forward<TArgs>(arguments)...));

        if (!camera && entities.back()->hasComponent("camera")) {
             camera = entities.back()->getComponent<CameraComponent>("camera");
        }

        //entities.back()->setTag(tag);

        return entities.back()->getId();
    }
}
