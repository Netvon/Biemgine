#include "SnowmanAIEntity.h"

namespace spacebiem
{
    SnowmanAIEntity::SnowmanAIEntity(float x, float y, Color color, float w, float h, float mass) :
        AIEntity(x, y, color, w, h, mass, "textures/SnowManSpriteSheet-256.png", 8llu, true, false, true)
    {}
}
