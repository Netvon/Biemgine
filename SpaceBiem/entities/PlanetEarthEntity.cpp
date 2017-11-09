#include "Biemgine.h"

#include "PlanetEarthEntity.h"
#include "../components/AtmosphereComponent.h"
#include "../components/GravityComponent.h"

using biemgine::PositionComponent;
using biemgine::TextureComponent;
using biemgine::PhysicsComponent;
using biemgine::ColorComponent;
using biemgine::GroundComponent;
using biemgine::PhysicsComponentShape;

namespace spacebiem
{
    PlanetEarthEntity::PlanetEarthEntity(float x, float y, Color color, float w, float h, float atmosphere = 1)
    {
        addComponent("position", new PositionComponent(x, y));
        addComponent("texture", new TextureComponent("textures/earth-plain.png", 0.f, 0.f, w, h, 2u));
        addComponent("texture", new TextureComponent("textures/atmosphere_clouds.png", 0.f - ((w * 2.5f / 2) - w / 2), 0 - ((h * 2.5f / 2) - h / 2), w * 2.5f, h * 2.5f, 9999u));
        addComponent("texture", new TextureComponent("textures/earth-TypeA.png", 0 - ((w*1.19f / 2) - w / 2), 0 - ((h*1.19f / 2) - h / 2), w*1.19f, h*1.19f, 1u));
        addComponent("texture", new TextureComponent("textures/atmosphere.png", w / -2.f, h / -2.f, w * 2.f, h * 2.f));
        addComponent("texture", new TextureComponent("textures/gravityField.png", w / -2.f, h / -2.f, w * 2.f, h * 2.f));
        addComponent("physics", new PhysicsComponent(w, h, true, PhysicsComponentShape::CIRCLE));
        addComponent("color", new ColorComponent(color));
        addComponent("atmosphere", new AtmosphereComponent(x + (w / 2), y + (h / 2), w, atmosphere));
        addComponent("ground", new GroundComponent);
        addComponent("gravity", new GravityComponent(w / -2.f, h / -2.f, w * 2.f, h * 2.f, w));
    }
}
