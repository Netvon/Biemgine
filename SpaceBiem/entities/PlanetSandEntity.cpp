#include "PlanetSandEntity.h"

namespace spacebiem
{
    PlanetSandEntity::PlanetSandEntity(float x, float y, Color color, float w, float h, int pScoreBonus, float atmosphere, string pName) :
        PlanetEntity(x, y, color, w, h, "textures/sand-plain.png", "textures/sand-TypeA.png", pScoreBonus, pName)
    {
        createAtmosphere(x, y, w, h, atmosphere, false, color);
    }
}
