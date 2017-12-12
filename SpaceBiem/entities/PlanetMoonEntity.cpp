#include "PlanetMoonEntity.h"

using biemgine::AudioComponent;

namespace spacebiem
{
    PlanetMoonEntity::PlanetMoonEntity(float x, float y, Color color, float w, float h, int pScoreBonus, string pName, bool scoreGiven) :
        PlanetEntity(x, y, color, w, h, "textures/moon-plain.png", "textures/moon-TypeA.png", pScoreBonus, pName, scoreGiven)
    {
        setTag("moon");
        createScoreBonus(pScoreBonus, scoreGiven);
    }
}
