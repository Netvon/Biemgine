
#include "PlanetEntity.h"

using biemgine::PositionComponent;
using biemgine::PhysicsComponent;
using biemgine::PhysicsComponentShape;
using biemgine::ColorComponent;
using biemgine::CollidableComponent;
using biemgine::GroundComponent;
using biemgine::TextureComponent;
using biemgine::TextComponent;

#include "../components/GravityComponent.h"
#include "../components/AtmosphereComponent.h"
#include "../components/ScoreBonusComponent.h"

namespace spacebiem
{
    PlanetEntity::PlanetEntity(float x, float y, Color color, float w, float h, string texture, string borderTexture, int pScoreBonus, string pName)
    {
        addComponent("position", new PositionComponent(x, y));
        addComponent("physics", new PhysicsComponent(w, h, true, PhysicsComponentShape::CIRCLE));

        addComponent("texture", new TextureComponent(texture, 0.f, 0.f, w, h, 2u));
        addComponent("texture", new TextureComponent(borderTexture, 0 - ((w*1.19f / 2) - w / 2), 0 - ((h*1.19f / 2) - h / 2), w*1.19f, h*1.19f, 1u));

        addComponent("collidable", new CollidableComponent);

        addComponent("ground", new GroundComponent);

        addComponent("gravity", new GravityComponent(w / -2.f, h / -2.f, w * 2.f, h * 2.f, w));
        addComponent("texture", new TextureComponent("textures/gravityField.png", w / -2.f, h / -2.f, w * 2.f, h * 2.f, 0u, true, "gravityfield", { color.r, color.g, color.b, 50}));
        addComponent("text", new TextComponent(to_string(pScoreBonus), { 255,255,255,255 }, w / 2, h / 2 + 20, false, true));
        addComponent("text", new TextComponent(pName, { 255,255,255,255 }, w / 2, h / 2 - 10, false, true));

        int flagHeight = 60;
        addComponent("texture", new TextureComponent("textures/flag.png", 0.f, 0.f, flagHeight * 0.56, flagHeight, 1u, false, "flag"));

        createScoreBonus(pScoreBonus);
    }

    void PlanetEntity::createAtmosphere(float x, float y, float w, float h, float atmosphere, bool shouldClouds, Color color)
    {
        PositionComponent* pc = getComponent<PositionComponent*>("position");

        addComponent("texture", new TextureComponent("textures/atmosphere.png", w / -2.f, h / -2.f, w * 2.f, h * 2.f, 0u, true, "atmosphere", color));
        addComponent("atmosphere", new AtmosphereComponent(pc, (w / 2), (h / 2), w, atmosphere));

        if (shouldClouds) {
            addComponent("texture", new TextureComponent("textures/atmosphere_clouds.png", 0.f - ((w * 2.5f / 2) - w / 2), 0 - ((h * 2.5f / 2) - h / 2), w * 2.5f, h * 2.5f, 10u));
        }
    }

    void PlanetEntity::createScoreBonus(int pScoreBonus)
    {
        addComponent("scorebonus", new ScoreBonusComponent(pScoreBonus));
    }
}
