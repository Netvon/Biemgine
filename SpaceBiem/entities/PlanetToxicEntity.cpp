#include "PlanetToxicEntity.h"

namespace spacebiem
{
    PlanetToxicEntity::PlanetToxicEntity(float x, float y, Color color, float w, float h, int pScoreBonus, float atmosphere, string pName) :
        PlanetEntity(x, y, color, w, h, "textures/moon-plain.png", "textures/moon-TypeA.png", pScoreBonus, pName)
    {
        setTag("toxic");
        createAtmosphere(x, y, w, h, atmosphere, false, color);
    }
}
