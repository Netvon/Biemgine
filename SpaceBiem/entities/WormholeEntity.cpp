#include "Biemgine.h"

#include "WormholeEntity.h"
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
    WormholeEntity::WormholeEntity(float x, float y, Color color, float w, float h, int pScoreBonus, float atmosphere, const string& pName, bool scoreGiven) :
        PlanetEntity(x, y, color, w, h, "textures/wormhole-plain.png", "textures/wormhole-TypeA.png", pScoreBonus, pName, scoreGiven)
    {
        setTag("wormhole");
        addComponent("texture", new TextureComponent("textures/wormhole-TypeB.png", 0.f, 0.f, w, h, 2u, true, "background_B"));
        //addComponent("audio", new AudioComponent("audio/earth.mp3", -1, -1, 48, 1000));
    }
}
