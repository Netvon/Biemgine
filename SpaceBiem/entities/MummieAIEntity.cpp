#include "MummieAIEntity.h"

namespace spacebiem
{
    MummieAIEntity::MummieAIEntity(float x, float y, Color color, float w, float h, float mass) :
        AIEntity(x, y, color, w, h, mass, "textures/MummieSpriteSheet2.png", 10llu, true, true, true)
    {}
}
