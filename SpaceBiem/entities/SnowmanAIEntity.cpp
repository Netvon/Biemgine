#include "SnowmanAIEntity.h"

using biemgine::AnimationDef;
using biemgine::TextureRowDef;
using biemgine::TextureColumnDef;

namespace spacebiem
{
    SnowmanAIEntity::SnowmanAIEntity(float x, float y, Color color, float w, float h, float mass) :
        AIEntity(x, y, color, w, h, mass, "textures/SnowManSpriteSheet-256.png", 8llu, true, false, true, {
            {
                "walk",
                TextureColumnDef{ 8llu, 256 }, TextureRowDef{ 1llu, 256 }
            }
        })
    {
        getComponent<AIComponent>("ai")->setName("snowman");
    }
}
