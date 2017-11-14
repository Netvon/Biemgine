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
    PlanetEarthEntity::PlanetEarthEntity(float x, float y, Color color, float w, float h, float atmosphere) :
        PlanetEntity(x, y, color, w, h, "textures/earth-plain.png", "textures/earth-TypeA.png")
    {
        createAtmosphere(x, y, w, h, atmosphere, "textures/atmosphere.png", true);
    }
}
