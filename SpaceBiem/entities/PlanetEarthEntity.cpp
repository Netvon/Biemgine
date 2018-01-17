#include "Biemgine.h"

#include "PlanetEarthEntity.h"
#include "../components/AtmosphereComponent.h"
#include "../components/GravityComponent.h"

using biemgine::AudioComponent;
using biemgine::PositionComponent;
using biemgine::TextureComponent;
using biemgine::PhysicsComponent;
using biemgine::ColorComponent;
using biemgine::GroundComponent;
using biemgine::PhysicsComponentShape;

namespace spacebiem
{
    PlanetEarthEntity::PlanetEarthEntity(float x, float y, Color color, float w, float h, int pScoreBonus, float atmosphere, const string& pName, bool scoreGiven, const string& border) :
        PlanetEntity(x, y, color, w, h, "textures/earth-plain.png", border, pScoreBonus, pName, scoreGiven)
    {
        setTag("earth");
        createAtmosphere(x, y, w, h, atmosphere, true, color);
        addComponent("audio", new AudioComponent("audio/earth.mp3", -1, -1, 48, 1000));
        createScoreBonus(pScoreBonus, scoreGiven);
    }
}
