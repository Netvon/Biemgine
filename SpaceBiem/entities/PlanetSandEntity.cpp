#include "PlanetSandEntity.h"

using biemgine::AudioComponent;

namespace spacebiem
{
    PlanetSandEntity::PlanetSandEntity(float x, float y, Color color, float w, float h, int pScoreBonus, float atmosphere, string pName) :
        PlanetEntity(x, y, color, w, h, "textures/sand-plain.png", "textures/sand-TypeA.png", pScoreBonus, pName)
    {
        setTag("sand");
        createAtmosphere(x, y, w, h, atmosphere, false, color);
        addComponent("audio", new AudioComponent("audio/sand.mp3", -1, -1, 20, 1000));
    }
}
