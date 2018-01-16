#include "MummieAIEntity.h"

using biemgine::AnimationDef;
using biemgine::TextureRowDef;
using biemgine::TextureColumnDef;

namespace spacebiem
{
    MummieAIEntity::MummieAIEntity(float x, float y, Color color, float w, float h, float mass) :
        AIEntity(x, y, color, w, h, mass, "textures/MummieSpriteSheet2.png", 10llu, true, true, true, {
            {
                "walk",
                TextureColumnDef{ 8llu, 256 }, TextureRowDef{ 1llu, 256 }
            },
            {
                "follow",
                TextureColumnDef{ 6llu, 256 }, TextureRowDef{ 1llu, 256, 256 },
                false
            }
        })
    {
		getComponent<AIComponent>("ai")->setName("mummie");
	}
}
