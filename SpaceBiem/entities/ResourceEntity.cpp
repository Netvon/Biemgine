#include "stdafx.h"
#include "ResourceEntity.h"

using biemgine::PositionComponent;
using biemgine::ColorComponent;
using biemgine::TextureComponent;
using biemgine::PhysicsComponent;
using biemgine::AffectedByGravityComponent;
using biemgine::PhysicsComponentShape;
using biemgine::CollidableComponent;

#include "../components/OxygenComponent.h"
#include "../components/ScoreComponent.h"
#include "../components/ScoreBonusComponent.h"
#include "../components/ResourceBonusComponent.h"

namespace spacebiem
{
    ResourceEntity::ResourceEntity(float x, float y, Color color, float w, float h, string rName, int scoreBonus)
    {
        addComponent("position", new PositionComponent(x, y));
        addComponent("color", new ColorComponent(color));
        addComponent("texture", new TextureComponent("textures/" + rName + ".png", 0, 0, w, h, 5u));
        addComponent("physics", new PhysicsComponent(w, h, false, PhysicsComponentShape::RECTANGLE, 1.0f));
        addComponent("affectedByGravity", new AffectedByGravityComponent(true));
        addComponent("scorebonus", new ScoreBonusComponent(scoreBonus));
        addComponent("resourcebonus", new ResourceBonusComponent(rName, 1));
        addComponent("collidable", new CollidableComponent);
    }
}