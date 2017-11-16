#include "PlanetSandEntity.h"

namespace spacebiem
{
    PlanetSandEntity::PlanetSandEntity(float x, float y, Color color, float w, float h, int pScoreBonus, float atmosphere) :
        PlanetEntity(x, y, color, w, h, "textures/sand-plain.png", "textures/sand-TypeA.png", pScoreBonus)
    {
        createAtmosphere(x, y, w, h, atmosphere);
    }
}
