#include "stdafx.h"
#include "ResourceEntity.h"

using biemgine::PositionComponent;
using biemgine::ColorComponent;
using biemgine::TextureComponent;
using biemgine::PhysicsComponent;
using biemgine::AffectedByGravityComponent;
using biemgine::PhysicsComponentShape;
using biemgine::CollidableComponent;
using biemgine::GroundedComponent;
using biemgine::AudioComponent;

#include "../components/OxygenComponent.h"
#include "../components/ScoreComponent.h"
#include "../components/ScoreBonusComponent.h"
#include "../components/ResourceBonusComponent.h"

namespace spacebiem
{
    ResourceEntity::ResourceEntity(float x, float y, Color color, float w, float h, string rName, int scoreBonus)
    {
        addComponent<PositionComponent>("position", x, y);
        addComponent<ColorComponent>("color", color);
        addComponent<TextureComponent>("texture","textures/" + rName + ".png", 0, 0, static_cast<int>(w), static_cast<int>(h), 5u, true, "background");
        addComponent<PhysicsComponent>("physics", w, h, false, PhysicsComponentShape::RECTANGLE, 0.1f);
        addComponent<AffectedByGravityComponent>("affectedByGravity", true);
        addComponent<ScoreBonusComponent>("scorebonus", scoreBonus);
        addComponent<ResourceBonusComponent>("resourcebonus", rName, 1);
        addComponent<CollidableComponent>("collidable", CollisionCategory::RESOURCE, CollisionCategory::PLANET | CollisionCategory::PLAYER);
        addComponent<GroundedComponent>("grounded");
        addComponent<AudioComponent>("audio", "audio/" + rName + ".mp3",0, -1, 48);

        setTag("resource");
    }
}
