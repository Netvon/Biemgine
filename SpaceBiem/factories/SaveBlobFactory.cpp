#include "Biemgine.h"

using biemgine::PositionComponent;

#include "../components/ScoreComponent.h"
#include "../components/OxygenComponent.h"
#include "SaveBlobEntityBuilder.h"
#include "SaveBlobFactory.h"
#include "..\entities\PlayerEntity.h"

#include "..\entities\PlanetEarthEntity.h"
#include "..\entities\PlanetSandEntity.h"
#include "..\entities\PlanetToxicEntity.h"
#include "..\entities\PlanetMoonEntity.h"

#include <typeindex>

namespace spacebiem
{
    vector<string> SaveBlobFactory::createFromEntities(const vector<Entity *> & entities)
    {
        vector<string> blob;

        blob.push_back("entity_id_type,component_type,value_1,value_2,value_3,value_4");

        for (auto it = entities.begin(); it != entities.end(); it++) {
            string entityBlob = createFromEntity(*(*it));

            if(!entityBlob.empty())
                blob.push_back(entityBlob);
        }

        return blob;
    }

    string SaveBlobFactory::createFromEntity(const Entity & entity)
    {
        SaveBlobEntityBuilder saveBlobEntityBuilder{};
        if (!saveBlobEntityBuilder.prepare(entity))
            return string();

        if (entity.hasComponent("position")) {
            saveBlobEntityBuilder.writePosition(*entity.getComponent<PositionComponent*>("position"));
        }

        if (entity.hasComponent("score")) {
            saveBlobEntityBuilder.writeScore(*entity.getComponent<ScoreComponent*>("score"));
        }

        if (entity.hasComponent("oxygen")) {
            saveBlobEntityBuilder.writeOxygen(*entity.getComponent<OxygenComponent*>("oxygen"));
        }

        if (typeid(entity) == typeid(PlayerEntity)) {
            saveBlobEntityBuilder.writeResource(*entity.getComponent<ResourceComponent*>("resources"));
        }

        // visited
        map<type_index, bool> planetTypes {
            { type_index(typeid(PlanetEarthEntity)), true },
            { type_index(typeid(PlanetMoonEntity)), true },
            { type_index(typeid(PlanetToxicEntity)), true },
            { type_index(typeid(PlanetSandEntity)), true }
        };

        auto find = planetTypes.find(type_index(typeid(entity)));

        if (find != planetTypes.end()) {
            saveBlobEntityBuilder.writeCollidable(*entity.getComponent<CollidableComponent*>("collidable"));

            // flag position
            auto components = entity.getComponents<TextureComponent*>("texture");

            for (auto it = components.begin(); it != components.end(); ++it)
            {
                auto component = (*it);
                if (component->getTag() != "flag") continue;

                saveBlobEntityBuilder.writeFlag(*component);
            }
        }
        
        return saveBlobEntityBuilder.build();
    }
}
