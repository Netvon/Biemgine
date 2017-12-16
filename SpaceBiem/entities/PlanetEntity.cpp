
#include "PlanetEntity.h"

using biemgine::PositionComponent;
using biemgine::PhysicsComponent;
using biemgine::PhysicsComponentShape;
using biemgine::ColorComponent;
using biemgine::CollidableComponent;
using biemgine::GroundComponent;
using biemgine::TextureComponent;
using biemgine::TextComponent;
using biemgine::ScriptComponent;
using biemgine::RandomGenerator;

#include "../components/GravityComponent.h"
#include "../components/AtmosphereComponent.h"
#include "../components/ScoreBonusComponent.h"
#include "..\globals\Fonts.h"

namespace spacebiem
{
    PlanetEntity::PlanetEntity(float x, float y, Color color, float w, float h, const string& texture, const string& borderTexture, int pScoreBonus, const string& pName, bool scoreGiven)
    {
        float rot = RandomGenerator::getInstance().generate(0.0f, 360.0f);

        addComponent("position", new PositionComponent(x, y));
        addComponent("physics", new PhysicsComponent(w, h, true, PhysicsComponentShape::CIRCLE));

        addComponent("texture", new TextureComponent(texture, 0.f, 0.f, w, h, 2u, true, "background"));
        addComponent("texture", new TextureComponent(borderTexture, 0.f - ((w*1.19f / 2.f) - w / 2.f), 0.f - ((h*1.19f / 2.f) - h / 2.f), w*1.19f, h*1.19f, 1u, true, "border", Color::White(), rot));

        addComponent("collidable", new CollidableComponent(CollisionCategory::PLANET, CollisionCategory::PLAYER | CollisionCategory::AI | CollisionCategory::RESOURCE));;

        addComponent("ground", new GroundComponent);

        addComponent("gravity", new GravityComponent(w / -2.f, h / -2.f, w * 2.f, h * 2.f, w));
        addComponent("texture", new TextureComponent("textures/gravityField.png", w / -2.f, h / -2.f, w * 2.f, h * 2.f, 0u, true, "gravityfield", { color.r, color.g, color.b, 50}));
        addComponent("text", new TextComponent(Fonts::Roboto(), to_string(pScoreBonus), { 255,255,255, 50 }, true, w / 2.f, h / 2.f + 20.f, scoreGiven));
        addComponent("text", new TextComponent(Fonts::Roboto(), pName, { 255,255,255,255 }, true, w / 2.f, h / 2.f - 10.f, scoreGiven, "name"));

        int flagHeight = 60;
        addComponent("texture", new TextureComponent("textures/flag.png", 0.f, 0.f, flagHeight * 0.56f, flagHeight, 1u, false, "flag"));

    }

    void PlanetEntity::createAtmosphere(float x, float y, float w, float h, float atmosphere, bool shouldClouds, Color color)
    {
        auto pc = getComponent<PositionComponent>("position");

        addComponent("texture", new TextureComponent("textures/atmosphere.png", w / -2.f, h / -2.f, w * 2.f, h * 2.f, 0u, true, "atmosphere", color));
        addComponent("atmosphere", new AtmosphereComponent(pc, (w / 2), (h / 2), w, atmosphere));

        if (shouldClouds) {

            float rot = RandomGenerator::getInstance().generate(0.0f, 360.0f);

            addComponent("texture", new TextureComponent("textures/atmosphere_clouds.png", 0.f - ((w * 2.5f / 2.f) - w / 2.f), 0 - ((h * 2.5f / 2.f) - h / 2.f), w * 2.5f, h * 2.5f, 10u, true, "clouds", Color::White(), rot));

            addComponent<ScriptComponent>("script",
            [this, textures = getComponents<TextureComponent>("texture")](float deltaTime)
            {
                for (auto tex : textures) {
                    if (tex->getTag() == "clouds") {
                        tex->setRotation(tex->getRotation() + deltaTime);
                    }
                }
            });
        }
    }

    void PlanetEntity::createScoreBonus(int pScoreBonus, bool scoreGiven)
    {
        addComponent("scorebonus", new ScoreBonusComponent(pScoreBonus, scoreGiven));
    }
}
