#include "PlanetLavaEntity.h"

namespace spacebiem
{
    PlanetLavaEntity::PlanetLavaEntity(float x, float y, Color color, float w, float h, int pScoreBonus, float atmosphere, string pName) :
        PlanetEntity(x, y, color, w, h, "textures/lava-plain.png", "textures/lava-TypeA.png", pScoreBonus, pName)
    {
        setTag("lava");
        createAtmosphere(x, y, w, h, atmosphere, false, color);
    }
}
