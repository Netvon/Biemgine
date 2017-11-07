#pragma once
#include "..\entities\bmEntity.h"
#include "bmSystemManager.h"
#include <vector>

namespace biemgine {

    class bmEntityManager
    {
    public:
        ~bmEntityManager();
        int addEntity(bmEntity* entity);

        void updateEntities(bmSystemManager * manager);
        void updateEntities(bmSystemManager * manager, const float deltaTime);

        std::vector<bmEntity*> getEntities() const
        {
            return entities;
        }

    private:
        std::vector<bmEntity*> entities;

    };
}
