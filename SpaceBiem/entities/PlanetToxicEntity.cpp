#include "PlanetToxicEntity.h"

using biemgine::AudioComponent;

namespace spacebiem
{
    PlanetToxicEntity::PlanetToxicEntity(float x, float y, Color color, float w, float h, int pScoreBonus, float atmosphere, string pName, bool scoreGiven) :
        PlanetEntity(x, y, color, w, h, "textures/toxic-plain.png", "textures/toxic-TypeA.png", pScoreBonus, pName, scoreGiven)
    {
        setTag("toxic");
        createAtmosphere(x, y, w, h, atmosphere, false, color);
        addComponent("audio", new AudioComponent("audio/toxic.mp3", -1, -1, 32, 1000));
        createScoreBonus(pScoreBonus, scoreGiven);
    }
}
