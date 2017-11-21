#pragma once

#include "stdafx.h"
#include <list>

using std::string;
using std::list;

#include "Biemgine.h"

using biemgine::PositionComponent;
using biemgine::CollidableComponent;
using biemgine::Entity;

#include "../components/ScoreComponent.h"
#include "../components/OxygenComponent.h"
#include "../components/ResourceComponent.h"

#include "SaveBlobEntityComponentBuilder.h"

namespace spacebiem
{
    class SaveBlobEntityBuilder
    {
    public:
        bool prepare(const Entity & entity);
        void writePosition(const PositionComponent & position);
        void writeScore(const ScoreComponent & score);
        void writeOxygen(const OxygenComponent & oxygen);
        void writeCollidable(const CollidableComponent & collidable);
        void writeResource(const ResourceComponent & resource);
        string build();

    private:
        string entityName;
        list<string> componentBlobs;
        string blob;

        SaveBlobEntityComponentBuilder saveBlobEntityComponentBuilder;
    };
}
