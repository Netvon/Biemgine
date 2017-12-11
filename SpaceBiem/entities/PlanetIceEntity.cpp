#include "PlanetIceEntity.h"

namespace spacebiem
{
    PlanetIceEntity::PlanetIceEntity(float x, float y, Color color, float w, float h, int pScoreBonus, float atmosphere, string pName) :
        PlanetEntity(x, y, color, w, h, "textures/ice-plain.png", "textures/ice-TypeA.png", pScoreBonus, pName)
    {
        setTag("ice");
        createAtmosphere(x, y, w, h, atmosphere, false, color);
        createScoreBonus(pScoreBonus);
    }
}
