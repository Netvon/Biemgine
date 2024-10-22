#include "SaveBlobEntityComponentBuilder.h"
#include "SaveBlobEntityBuilder.h"

#include <map>
#include <typeindex>

#include "..\entities\PlayerEntity.h"
#include "..\entities\PlanetEarthEntity.h"
#include "..\entities\PlanetMoonEntity.h"
#include "..\entities\PlanetToxicEntity.h"
#include "..\entities\PlanetSandEntity.h"
#include "..\entities\PlanetIceEntity.h"
#include "..\entities\PlanetLavaEntity.h"

#include "..\entities\WormholeEntity.h"

#include "..\entities\ResourceEntity.h"

#include "..\entities\MummieAIEntity.h"
#include "..\entities\SnowmanAIEntity.h"

using std::map;
using std::sprintf;
using std::type_index;
using biemgine::Vector;

namespace spacebiem
{
    bool SaveBlobEntityBuilder::prepare(const Entity & entity)
    {
        map<type_index, string> typemap{
            { type_index(typeid(PlayerEntity)), "player" },
            { type_index(typeid(PlanetEarthEntity)), "earth" },
            { type_index(typeid(PlanetMoonEntity)), "moon" },
            { type_index(typeid(PlanetToxicEntity)), "toxic" },
            { type_index(typeid(PlanetSandEntity)), "sand" },
            { type_index(typeid(PlanetIceEntity)), "ice" },
            { type_index(typeid(PlanetLavaEntity)), "lava" },
            { type_index(typeid(WormholeEntity)), "wormhole" },
            { type_index(typeid(ResourceEntity)), "resource" },
            { type_index(typeid(MummieAIEntity)), "aimummie" },
            { type_index(typeid(SnowmanAIEntity)), "aisnowman" }
        };

        auto find = typemap.find(type_index(typeid(entity)));

        if (find == typemap.end())
            return false;

        entityName = to_string(entity.getId()) + "_" + find->second;
        return true;
    }

    void SaveBlobEntityBuilder::writePosition(const PositionComponent & position, const TextureComponent & backgroundTexture)
    {
        saveBlobEntityComponentBuilder.prepare("position_component");

        saveBlobEntityComponentBuilder.addValue(to_string(position.getOriginX()));
        saveBlobEntityComponentBuilder.addValue(to_string(position.getOriginY()));
        saveBlobEntityComponentBuilder.addValue(to_string(backgroundTexture.getWidth()));
        saveBlobEntityComponentBuilder.addValue(to_string(backgroundTexture.getHeight()));

        componentBlobs.push_back(saveBlobEntityComponentBuilder.build());
    }

    void SaveBlobEntityBuilder::writeScore(const ScoreComponent & score)
    {
        saveBlobEntityComponentBuilder.prepare("score_component");

        saveBlobEntityComponentBuilder.addValue(to_string(score.getScore()));

        componentBlobs.push_back(saveBlobEntityComponentBuilder.build());
    }

    void SaveBlobEntityBuilder::writeOxygen(const OxygenComponent & oxygen)
    {
        saveBlobEntityComponentBuilder.prepare("oxygen_component");

        saveBlobEntityComponentBuilder.addValue(to_string(oxygen.getOxygenAmount()));

        componentBlobs.push_back(saveBlobEntityComponentBuilder.build());
    }

    void SaveBlobEntityBuilder::writeResource(const ResourceComponent & resource)
    {
        saveBlobEntityComponentBuilder.prepare("resource_component");

        map<string, int> resources = resource.getResources();

        for (auto it = resources.begin(); it != resources.end(); ++it) {
            saveBlobEntityComponentBuilder.addValue(to_string((*it).second));
        }

        string componentBlob = saveBlobEntityComponentBuilder.build();
        componentBlobs.push_back(componentBlob);
    }

    string SaveBlobEntityBuilder::build()
    {
        string blob;

        for (auto it = componentBlobs.begin(); it != componentBlobs.end(); ++it) {

            if (it != componentBlobs.begin())
                blob += "\n";

            blob += entityName + "," + (*it);
        }

        return blob;
    }

    void SaveBlobEntityBuilder::writeFlag(const TextureComponent & flagTexture)
    {
        if (!flagTexture.isVisible()) return;

        saveBlobEntityComponentBuilder.prepare("flag_component");

        saveBlobEntityComponentBuilder.addValue(to_string(flagTexture.getOffsetX()));
        saveBlobEntityComponentBuilder.addValue(to_string(flagTexture.getOffsetY()));
        saveBlobEntityComponentBuilder.addValue(to_string(flagTexture.getRotation()));
        saveBlobEntityComponentBuilder.addValue(to_string(flagTexture.isVisible()));

        string componentBlob = saveBlobEntityComponentBuilder.build();
        componentBlobs.push_back(componentBlob);
    }

    void SaveBlobEntityBuilder::writePhysics(const PhysicsComponent & physics, const PositionComponent & position)
    {
        saveBlobEntityComponentBuilder.prepare("physics_component");

        saveBlobEntityComponentBuilder.addValue(to_string(physics.getVelocity().x));
        saveBlobEntityComponentBuilder.addValue(to_string(physics.getVelocity().y));
        saveBlobEntityComponentBuilder.addValue(to_string(position.getRotation()));

        string componentBlob = saveBlobEntityComponentBuilder.build();
        componentBlobs.push_back(componentBlob);
    }

    void SaveBlobEntityBuilder::writeResourceBonus(const ResourceBonusComponent & resourceBonus)
    {
        saveBlobEntityComponentBuilder.prepare("resource_bonus_component");

        saveBlobEntityComponentBuilder.addValue(resourceBonus.getName());
        saveBlobEntityComponentBuilder.addValue(to_string(resourceBonus.getAmount()));

        string componentBlob = saveBlobEntityComponentBuilder.build();
        componentBlobs.push_back(componentBlob);
    }

    void SaveBlobEntityBuilder::writeScoreBonus(const ScoreBonusComponent & scoreBonus)
    {
        saveBlobEntityComponentBuilder.prepare("score_bonus_component");

        saveBlobEntityComponentBuilder.addValue(to_string(scoreBonus.getScoreBonus()));
        saveBlobEntityComponentBuilder.addValue(to_string(scoreBonus.isScoreGiven()));

        string componentBlob = saveBlobEntityComponentBuilder.build();
        componentBlobs.push_back(componentBlob);
    }

    void SaveBlobEntityBuilder::writeName(const TextComponent & name)
    {
        saveBlobEntityComponentBuilder.prepare("name_component");

        saveBlobEntityComponentBuilder.addValue(name.getText());

        string componentBlob = saveBlobEntityComponentBuilder.build();
        componentBlobs.push_back(componentBlob);
    }
}
