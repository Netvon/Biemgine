#include "PlanetLavaEntity.h"

using biemgine::AudioComponent;

namespace spacebiem
{
    PlanetLavaEntity::PlanetLavaEntity(float x, float y, Color color, float w, float h, int pScoreBonus, float atmosphere, string pName) :
        PlanetEntity(x, y, color, w, h, "textures/lava-plain.png", "textures/lava-TypeA.png", pScoreBonus, pName)
    {
        setTag("lava");
        createAtmosphere(x, y, w, h, atmosphere, false, color);
        addComponent("audio", new AudioComponent("audio/lava.mp3", -1, -1, 64, 1000));
    }
}
