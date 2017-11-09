#include "Biemgine.h"

#include "bmPlanetEarthEntity.h"
#include "../components/bmAtmosphereComponent.h"
#include "../components/bmGravityComponent.h"

using biemgine::bmPositionComponent;
using biemgine::bmTextureComponent;
using biemgine::bmPhysicsComponent;
using biemgine::bmColorComponent;
using biemgine::bmGroundComponent;
using biemgine::PhysicsComponentShape;

namespace spacebiem
{
    bmPlanetEarthEntity::bmPlanetEarthEntity(float x, float y, bmColor color, float w, float h)
    {
        addComponent("position", new bmPositionComponent(x, y));
        addComponent("texture", new bmTextureComponent("textures/earth-plain.png", 0.f, 0.f, w, h, 2u));
        addComponent("texture", new bmTextureComponent("textures/atmosphere_clouds.png", 0.f - ((w * 2.5f / 2) - w / 2), 0 - ((h * 2.5f / 2) - h / 2), w * 2.5f, h * 2.5f, 9999u));
        addComponent("texture", new bmTextureComponent("textures/earth-TypeA.png", 0 - ((w*1.19f / 2) - w / 2), 0 - ((h*1.19f / 2) - h / 2), w*1.19f, h*1.19f, 1u));
        addComponent("texture", new bmTextureComponent("textures/atmosphere.png", w / -2.f, h / -2.f, w * 2.f, h * 2.f));
        addComponent("texture", new bmTextureComponent("textures/gravityField.png", w / -2.f, h / -2.f, w * 2.f, h * 2.f));
        addComponent("physics", new bmPhysicsComponent(w, h, true, PhysicsComponentShape::CIRCLE));
        addComponent("color", new bmColorComponent(color));
        addComponent("atmosphere", new bmAtmosphereComponent(x + (w / 2), y + (h / 2), w));
        addComponent("ground", new bmGroundComponent);
        addComponent("gravity", new bmGravityComponent(w / -2.f, h / -2.f, w * 2.f, h * 2.f, w));
    }
}
