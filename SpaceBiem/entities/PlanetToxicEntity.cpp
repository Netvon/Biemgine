#include "PlanetToxicEntity.h"

namespace spacebiem
{
    PlanetToxicEntity::PlanetToxicEntity(float x, float y, Color color, float w, float h, int pScoreBonus, float atmosphere) :
        PlanetEntity(x, y, color, w, h, "textures/moon-plain.png", "textures/moon-TypeA.png", pScoreBonus)
    {}
}
