#include "Biemgine.h"

#include "WormholeEntity.h"
#include "../components/GravityComponent.h"

using biemgine::PositionComponent;
using biemgine::PhysicsComponent;
using biemgine::PhysicsComponentShape;
using biemgine::ColorComponent;
using biemgine::CollidableComponent;
using biemgine::GroundComponent;
using biemgine::TextureComponent;
using biemgine::AnimatedTextureComponent;
using biemgine::TextureColumnDef;
using biemgine::TextureRowDef;
using biemgine::TextComponent;
using biemgine::ScriptComponent;
using biemgine::RandomGenerator;

namespace spacebiem
{
    WormholeEntity::WormholeEntity(float x, float y, Color color, float w, float h)
    {
        float rot = RandomGenerator::getInstance().generate(0.0f, 360.0f);

        setTag("wormhole");

        addComponent("position", new PositionComponent(x, y));
        addComponent("physics", new PhysicsComponent(w , h, true, PhysicsComponentShape::CIRCLE));

        addComponent("texture", new TextureComponent("textures/wormhole-TypeA.png", 0.f - (w / 2), 0.f - (h / 2), w * 2, h * 2, 1u, true, "border", Color::White(), rot));
        addComponent("texture", new TextureComponent("textures/wormhole-TypeB.png", 0.f - (w / 2), 0.f - (h / 2), w * 2, h * 2, 1u, true, "border_B", Color::White(), rot));
        addComponent("texture", new TextureComponent("textures/wormhole-plain.png", 0.f , 0.f , w, h, 2u, true, "background"));

        addComponent<ScriptComponent>("script",
        [this, textures = getComponents<TextureComponent>("texture")](float deltaTime)
        {
            for (auto tex : textures) {
                if (tex->getTag() == "border_B") {
                    tex->setRotation(tex->getRotation() + (deltaTime * 10));
                }
                if (tex->getTag() == "border") {
                    tex->setRotation(tex->getRotation() + (deltaTime * 50));
                }
            }
        });

        addComponent("collidable", new CollidableComponent(CollisionCategory::PLANET, CollisionCategory::PLAYER | CollisionCategory::AI | CollisionCategory::RESOURCE));;

        addComponent("ground", new GroundComponent);

        addComponent("gravity", new GravityComponent(w / -2.f, h / -2.f, w * 2.f, h * 2.f, w));
        addComponent("texture", new TextureComponent("textures/gravityField.png", w / -2.f, h / -2.f, w * 2.f, h * 2.f, 0u, true, "gravityfield", { color.r, color.g, color.b, 50 }));
    }
}
