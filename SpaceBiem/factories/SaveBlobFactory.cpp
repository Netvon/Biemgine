#include "Biemgine.h"

using biemgine::PositionComponent;

#include "../components/ScoreComponent.h"
#include "../components/ScoreBonusComponent.h"
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
    vector<string> SaveBlobFactory::createFromEntities(shared_ptr<EntityManager> entities)
    {
        vector<string> blob;

        blob.push_back("entity_id_type,component_type,value_1,value_2,value_3,value_4");

        for (auto it = entities->begin(); it != entities->end(); it++) {
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
            auto backgroundTexture = getTextureComponentByTag(entity, "background");

            saveBlobEntityBuilder.writePosition(*entity.getComponent<PositionComponent>("position"), backgroundTexture);
        }

        if (entity.hasComponent("score")) {
            saveBlobEntityBuilder.writeScore(*entity.getComponent<ScoreComponent>("score"));
        }

        if (entity.hasComponent("oxygen")) {
            saveBlobEntityBuilder.writeOxygen(*entity.getComponent<OxygenComponent>("oxygen"));
        }

        if (entity.hasComponent("physics") && entity.hasComponent("position")) {
            saveBlobEntityBuilder.writePhysics(*entity.getComponent<PhysicsComponent>("physics"), *entity.getComponent<PositionComponent>("position"));
        }

        if (typeid(entity) == typeid(PlayerEntity)) {
            saveBlobEntityBuilder.writeResource(*entity.getComponent<ResourceComponent>("resources"));
        }

        if (entity.hasComponent("resourcebonus")) {
            saveBlobEntityBuilder.writeResourceBonus(*entity.getComponent<ResourceBonusComponent>("resourcebonus"));
        }

        if(entity.hasComponent("scorebonus")) {
            saveBlobEntityBuilder.writeScoreBonus(*entity.getComponent<ScoreBonusComponent>("scorebonus"));
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
            auto flagTextureComponent = getTextureComponentByTag(entity, "flag");
            saveBlobEntityBuilder.writeFlag(flagTextureComponent);

            auto nameTextComponent = getTextComponentByTag(entity, "name");
            saveBlobEntityBuilder.writeName(nameTextComponent);
        }
        
        return saveBlobEntityBuilder.build();
    }

    TextureComponent & SaveBlobFactory::getTextureComponentByTag(const Entity & entity, const string & pTag)
    {
        auto components = entity.getComponents<TextureComponent>("texture");

        for (auto it = components.begin(); it != components.end(); ++it)
        {
            auto component = (*it);
            if (component->getTag() != pTag) continue;

            return *component;
        }
    }

    TextComponent & SaveBlobFactory::getTextComponentByTag(const Entity & entity, const string & pTag)
    {
        auto components = entity.getComponents<TextComponent>("text");

        for (auto it = components.begin(); it != components.end(); ++it)
        {
            auto component = (*it);
            if (component->getTag() != pTag) continue;

            return *component;
        }
    }
}
