#include "Biemgine.h"

#include "PlanetMoonEntity.h"
#include "../components/GravityComponent.h"

using biemgine::PositionComponent;
using biemgine::TextureComponent;
using biemgine::PhysicsComponent;
using biemgine::ColorComponent;
using biemgine::GroundComponent;
using biemgine::PhysicsComponentShape;

namespace spacebiem
{
    PlanetMoonEntity::PlanetMoonEntity(float x, float y, Color color, float w, float h)
    {
        addComponent("position", new PositionComponent(x, y));
        addComponent("texture", new TextureComponent("textures/moon-plain.png", 0, 0, w, h, 2u));
        addComponent("texture", new TextureComponent("textures/moon-TypeA.png", 0 - ((w*1.19f / 2) - w / 2), 0 - ((h*1.19f / 2) - h / 2), w*1.19f, h*1.19f, 1u));
        addComponent("texture", new TextureComponent("textures/gravityField.png", w / -2, h / -2, w * 2, h * 2));
        addComponent("physics", new PhysicsComponent(w, h, true, PhysicsComponentShape::CIRCLE));
        addComponent("color", new ColorComponent(color));
        addComponent("ground", new GroundComponent);
        addComponent("gravity", new GravityComponent(w / -2, h / -2, w * 2, h * 2, w));
    }
}
