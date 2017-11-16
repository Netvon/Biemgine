#pragma once
#include "dlldef.h"
#include "..\entities\Entity.h"
#include "SystemManager.h"
#include <vector>
#include <memory>

namespace biemgine
{
    class BIEMGINE EntityManager
    {
    public:
        ~EntityManager();
        int addEntity(Entity* entity);

        void updateEntities(std::shared_ptr<SystemManager> manager);
        void updateEntities(std::shared_ptr<SystemManager> manager, const float deltaTime);

        std::vector<Entity*> getEntities() const
        {
            return entities;
        }

        Entity* getEntity(int id) const;

        void removeDeadEntities();

    private:
        std::vector<Entity*> entities;
    };
}
