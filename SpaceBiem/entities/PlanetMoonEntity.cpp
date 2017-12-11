#include "PlanetMoonEntity.h"

using biemgine::AudioComponent;

namespace spacebiem
{
    PlanetMoonEntity::PlanetMoonEntity(float x, float y, Color color, float w, float h, int pScoreBonus, string pName) :
        PlanetEntity(x, y, color, w, h, "textures/moon-plain.png", "textures/moon-TypeA.png", pScoreBonus, pName)
    {
        setTag("moon");
        createScoreBonus(pScoreBonus);
    }
}
