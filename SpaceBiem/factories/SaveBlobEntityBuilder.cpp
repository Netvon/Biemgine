#include "SaveBlobEntityComponentBuilder.h"
#include "SaveBlobEntityBuilder.h"

#include <map>
#include <typeindex>

#include "..\entities\PlayerEntity.h"
#include "..\entities\PlanetEarthEntity.h"
#include "..\entities\PlanetMoonEntity.h"
#include "..\entities\PlanetToxicEntity.h"
#include "..\entities\PlanetSandEntity.h"

using std::map;
using std::sprintf;
using std::type_index;

namespace spacebiem
{
    bool SaveBlobEntityBuilder::prepare(const Entity & entity)
    {
        map<type_index, string> typemap{
            { type_index(typeid(PlayerEntity)), "player" },
            { type_index(typeid(PlanetEarthEntity)), "earth" },
            { type_index(typeid(PlanetMoonEntity)), "moon" },
            { type_index(typeid(PlanetToxicEntity)), "toxic" },
            { type_index(typeid(PlanetSandEntity)), "sand" }
        };

        auto find = typemap.find(type_index(typeid(entity)));

        if (find == typemap.end())
            return false;

        entityName = to_string(entity.getId()) + "_" + find->second;
        return true;
    }

    void SaveBlobEntityBuilder::writePosition(const PositionComponent & position)
    {
        saveBlobEntityComponentBuilder.prepare("position_component");

        saveBlobEntityComponentBuilder.addValue(to_string(position.getX()));
        saveBlobEntityComponentBuilder.addValue(to_string(position.getY()));
        saveBlobEntityComponentBuilder.addValue(to_string(position.getZ()));

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

    void SaveBlobEntityBuilder::writeCollidable(const CollidableComponent & collidable)
    {
        saveBlobEntityComponentBuilder.prepare("collidable_component");

        auto collisions = collidable.getCollisions();

        bool playerCollided = false;

        for (auto it = collisions.begin(); it != collisions.end(); ++it) {
            if (typeid(*it) == typeid(PlayerEntity)) {
                playerCollided = true;
                break;
            }
        }

        saveBlobEntityComponentBuilder.addValue(to_string(playerCollided));

        string componentBlob = saveBlobEntityComponentBuilder.build();
        componentBlobs.push_back(componentBlob);
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

    void SaveBlobEntityBuilder::writeFlag(const TextureComponent & texture)
    {
        saveBlobEntityComponentBuilder.prepare("flag_component");

        saveBlobEntityComponentBuilder.addValue(to_string(texture.getOffsetX()));
        saveBlobEntityComponentBuilder.addValue(to_string(texture.getOffsetY()));
        saveBlobEntityComponentBuilder.addValue(to_string(texture.getRotation()));

        string componentBlob = saveBlobEntityComponentBuilder.build();
        componentBlobs.push_back(componentBlob);
    }
}
