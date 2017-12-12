#include "PlanetIceEntity.h"

using biemgine::AudioComponent;

namespace spacebiem
{
    PlanetIceEntity::PlanetIceEntity(float x, float y, Color color, float w, float h, int pScoreBonus, float atmosphere, string pName, bool scoreGiven) :
        PlanetEntity(x, y, color, w, h, "textures/ice-plain.png", "textures/ice-TypeA.png", pScoreBonus, pName, scoreGiven)
    {
        setTag("ice");
        createAtmosphere(x, y, w, h, atmosphere, false, color);
        addComponent("audio", new AudioComponent("audio/ice.mp3", -1, -1, 64, 1000));
        createScoreBonus(pScoreBonus, scoreGiven);
    }
}
