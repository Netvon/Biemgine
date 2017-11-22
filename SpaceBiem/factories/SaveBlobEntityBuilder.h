#pragma once

#include "stdafx.h"
#include <list>

using std::string;
using std::list;

#include "Biemgine.h"

using biemgine::PositionComponent;
using biemgine::CollidableComponent;
using biemgine::TextureComponent;
using biemgine::PhysicsComponent;
using biemgine::Entity;

#include "../components/ScoreComponent.h"
#include "../components/OxygenComponent.h"
#include "../components/ResourceComponent.h"
#include "../components/ResourceBonusComponent.h"
#include "../components/ScoreBonusComponent.h"

#include "SaveBlobEntityComponentBuilder.h"

namespace spacebiem
{
    class SaveBlobEntityBuilder
    {
    public:
        bool prepare(const Entity & entity);
        void writePosition(const PositionComponent & position, const TextureComponent & backgroundTexture);
        void writeScore(const ScoreComponent & score);
        void writeOxygen(const OxygenComponent & oxygen);
        void writeVisited(const CollidableComponent & collidable, const TextureComponent & flagTexture);
        void writeResource(const ResourceComponent & resource);
        void writeFlag(const TextureComponent & flagTexture);
        void writePhysics(const PhysicsComponent & physics, const PositionComponent & position);
        void writeResourceBonus(const ResourceBonusComponent & resourceBonus);
        void writeScoreBonus(const ScoreBonusComponent & scoreBonus);
        string build();

    private:
        string entityName;
        list<string> componentBlobs;
        string blob;

        SaveBlobEntityComponentBuilder saveBlobEntityComponentBuilder;
    };
}
