#include "Biemgine.h"

using biemgine::PositionComponent;

#include "../components/ScoreComponent.h"
#include "../components/OxygenComponent.h"
#include "SaveBlobEntityBuilder.h"
#include "SaveBlobFactory.h"

namespace spacebiem
{
    vector<string> SaveBlobFactory::createFromEntities(const vector<Entity *> & entities)
    {
        vector<string> blob;

        blob.push_back("entity_id_type,component_type,value_1,value_2,value_3,value_4");

        for (auto it = entities.begin(); it != entities.end(); it++) {
            string entityBlob = createFromEntity(*(*it));
            blob.push_back(entityBlob);
        }

        return blob;
    }

    string SaveBlobFactory::createFromEntity(const Entity & entity)
    {
        SaveBlobEntityBuilder saveBlobEntityBuilder{};
        saveBlobEntityBuilder.prepare(entity);

        if (entity.hasComponent("position")) {
            saveBlobEntityBuilder.writePosition(*entity.getComponent<PositionComponent*>("position"));
        }

        if (entity.hasComponent("score")) {
            saveBlobEntityBuilder.writeScore(*entity.getComponent<ScoreComponent*>("score"));
        }

        if (entity.hasComponent("oxygen")) {
            saveBlobEntityBuilder.writeOxygen(*entity.getComponent<OxygenComponent*>("oxygen"));
        }

        if (typeid(entity).name() == "PlayerEntity") {
            saveBlobEntityBuilder.writeCollidable(*entity.getComponent<CollidableComponent*>("collidable"));
            saveBlobEntityBuilder.writeResource(*entity.getComponent<ResourceComponent*>("resources"));
        }
        
        return saveBlobEntityBuilder.build();
    }
}
