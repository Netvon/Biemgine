#include "PlanetMoonEntity.h"

namespace spacebiem
{
    PlanetMoonEntity::PlanetMoonEntity(float x, float y, Color color, float w, float h) :
        PlanetEntity(x, y, color, w, h, "textures/moon-plain.png", "textures/moon-TypeA.png")
    {}
}
