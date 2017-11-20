#include "SaveBlobEntityComponentBuilder.h"
#include "SaveBlobEntityBuilder.h"

#include <map>

using std::map;
using std::sprintf;

namespace spacebiem
{
    SaveBlobEntityBuilder::SaveBlobEntityBuilder()
    {
        saveBlobEntityComponentBuilder = new SaveBlobEntityComponentBuilder();
    }

    SaveBlobEntityBuilder::~SaveBlobEntityBuilder()
    {
        delete saveBlobEntityComponentBuilder;
    }

    void SaveBlobEntityBuilder::prepare(const Entity & entity)
    {
        const map<string, string> entityTypes = {
            { "PlayerEntity", "player" },
            { "PlanetEarthEntity", "earth" },
            { "PlanetMoonEntity", "moon" },
            { "PlanetToxicEntity", "toxic" },
            { "PlanetSandEntity", "sand" }
        };

        string entityType = entityTypes.at(typeid(entity).name());
        entityName = entity.getId() + "_" + entityType;
    }

    void SaveBlobEntityBuilder::writePosition(const PositionComponent & position)
    {
        saveBlobEntityComponentBuilder->prepare("position_component");

        saveBlobEntityComponentBuilder->addValue(to_string(position.getX()));
        saveBlobEntityComponentBuilder->addValue(to_string(position.getY()));
        saveBlobEntityComponentBuilder->addValue(to_string(position.getZ()));

        string componentBlob = saveBlobEntityComponentBuilder->build();
        componentBlobs.push_back(componentBlob);
    }

    void SaveBlobEntityBuilder::writeScore(const ScoreComponent & score)
    {
        saveBlobEntityComponentBuilder->prepare("score_component");

        saveBlobEntityComponentBuilder->addValue(to_string(score.getScore()));

        string componentBlob = saveBlobEntityComponentBuilder->build();
        componentBlobs.push_back(componentBlob);
    }

    void SaveBlobEntityBuilder::writeOxygen(const OxygenComponent & oxygen)
    {
        saveBlobEntityComponentBuilder->prepare("oxygen_component");

        saveBlobEntityComponentBuilder->addValue(to_string(oxygen.getOxygenAmount()));

        string componentBlob = saveBlobEntityComponentBuilder->build();
        componentBlobs.push_back(componentBlob);
    }

    void SaveBlobEntityBuilder::writeCollidable(const CollidableComponent & collidable)
    {
        saveBlobEntityComponentBuilder->prepare("collidable_component");

        auto collisions = collidable.getCollisions();

        bool playerCollided = false;

        for (auto it = collisions.begin(); it != collisions.end(); ++it) {
            if (typeid(*it).name() == "PlayerEntity") {
                playerCollided = true;
                break;
            }
        }

        saveBlobEntityComponentBuilder->addValue(to_string(playerCollided));

        string componentBlob = saveBlobEntityComponentBuilder->build();
        componentBlobs.push_back(componentBlob);
    }

    void SaveBlobEntityBuilder::writeResource(const ResourceComponent & resource)
    {
        saveBlobEntityComponentBuilder->prepare("resource_component");

        map<string, int> resources = resource.getResources();

        for (auto it = resources.begin(); it != resources.end(); ++it) {
            saveBlobEntityComponentBuilder->addValue(to_string((*it).second));
        }
    }

    string SaveBlobEntityBuilder::build()
    {
        string blob;

        for (auto it = componentBlobs.begin(); it != componentBlobs.end(); ++it) {
            blob += "\n";
            blob += entityName + "," + (*it);
        }

        return blob;
    }
}
