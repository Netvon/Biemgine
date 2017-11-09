#pragma once
#include "dlldef.h"
#include "..\entities\bmEntity.h"
#include "bmSystemManager.h"
#include <vector>
#include <memory>

namespace biemgine
{
    class BIEMGINE bmEntityManager
    {
    public:
        ~bmEntityManager();
        int addEntity(bmEntity* entity);

        void updateEntities(std::shared_ptr<bmSystemManager> manager);
        void updateEntities(std::shared_ptr<bmSystemManager> manager, const float deltaTime);

        std::vector<bmEntity*> getEntities() const
        {
            return entities;
        }

    private:
        std::vector<bmEntity*> entities;
    };
}
