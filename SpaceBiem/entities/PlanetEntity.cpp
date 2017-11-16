
#include "PlanetEntity.h"

using biemgine::PositionComponent;
using biemgine::PhysicsComponent;
using biemgine::PhysicsComponentShape;
using biemgine::ColorComponent;
using biemgine::CollidableComponent;
using biemgine::GroundComponent;
using biemgine::TextureComponent;

#include "../components/GravityComponent.h"
#include "../components/AtmosphereComponent.h"
#include "../components/ScoreBonusComponent.h"

namespace spacebiem
{
    PlanetEntity::PlanetEntity(float x, float y, Color color, float w, float h, string texture, string borderTexture)
    {
        addComponent("position", new PositionComponent(x, y));
        addComponent("physics", new PhysicsComponent(w, h, true, PhysicsComponentShape::CIRCLE));
        addComponent("color", new ColorComponent(color));

        addComponent("texture", new TextureComponent(texture, 0.f, 0.f, w, h, 2u));
        addComponent("texture", new TextureComponent(borderTexture, 0 - ((w*1.19f / 2) - w / 2), 0 - ((h*1.19f / 2) - h / 2), w*1.19f, h*1.19f, 1u));

        addComponent("collidable", new CollidableComponent);

        addComponent("ground", new GroundComponent);
        addComponent("gravity", new GravityComponent(w / -2.f, h / -2.f, w * 2.f, h * 2.f, w));
        addComponent("texture", new TextureComponent("textures/gravityField.png", w / -2.f, h / -2.f, w * 2.f, h * 2.f));
    }

    void PlanetEntity::createAtmosphere(float x, float y, float w, float h, float atmosphere, string texture, bool shouldClouds)
    {
        addComponent("texture", new TextureComponent(texture, w / -2.f, h / -2.f, w * 2.f, h * 2.f));
        addComponent("atmosphere", new AtmosphereComponent(x + (w / 2), y + (h / 2), w, atmosphere));

        if (shouldClouds) {
            addComponent("texture", new TextureComponent("textures/atmosphere_clouds.png", 0.f - ((w * 2.5f / 2) - w / 2), 0 - ((h * 2.5f / 2) - h / 2), w * 2.5f, h * 2.5f, 9999u));
        }
    }

    void PlanetEntity::createScoreBonus(int pScoreBonus)
    {
        addComponent("scorebonus", new ScoreBonusComponent(pScoreBonus));
    }
}
