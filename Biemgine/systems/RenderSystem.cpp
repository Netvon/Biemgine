#include "stdafx.h"
#include "RenderSystem.h"
#include "..\components\PositionComponent.h"
#include "..\components\ColorComponent.h"
#include "..\components\RectangleComponent.h"
#include "..\components\TextureComponent.h"
#include "..\entities\Entity.h"
#include "../devices/graphics/TextureFlip.h"

namespace biemgine
{
    RenderSystem::~RenderSystem() {}
 
    void RenderSystem::setGraphicsDevice(GraphicsDevice* graphicsDevice)
    {
        this->graphicsDevice = graphicsDevice;
    }

    void RenderSystem::update(const Entity& entity, const float deltaTime)
    {
        if (!entity.hasComponent("position"))
            return;

        auto pc = entity.getComponent<PositionComponent>("position");

        if (entity.hasComponent("text")) {
            auto txs = entity.getComponents<TextComponent>("text");

            for (auto tx : txs) {
                if (tx->isVisible()) {
                    textList.push_back(DrawText(
                        tx->getFont(),
                        tx->getText(),
                        static_cast<int>(pc->getX() + tx->getOffsetX()),
                        static_cast<int>(pc->getY() + tx->getOffsetY()),
                        tx->getColor(),
                        tx,
                        tx->isCenter()
                    ));
                }
            }
        }

        if (!entity.hasComponent("texture") && !entity.hasComponent("rectangle"))
            return;

        if (entity.hasComponent("texture")) {
            auto tc = entity.getComponents<TextureComponent>("texture");

            for (auto tex : tc) {
                if (!tex->isVisible()) continue;

                drawList.push_back(DrawTexture(
                    tex->getPath(),
                    static_cast<int>(pc->getX() + tex->getOffsetX()),
                    static_cast<int>(pc->getY() + tex->getOffsetY()),
                    tex->getWidth(),
                    tex->getHeight(),
                    pc->getRotation() + tex->getRotation(),
                    (entity.hasComponent("color")) ? entity.getComponent<ColorComponent>("color")->getColor() : tex->getColor(),
                    tex->getLayer(),
                    false,
                    tex->getFlip()
                ));
            }
        }

        if (entity.hasComponent("rectangle"))
        {
            auto rectangle = entity.getComponent<RectangleComponent>("rectangle");

            graphicsDevice->drawSquare(
                static_cast<int>(pc->getX()),
                static_cast<int>(pc->getY()),
                static_cast<int>(rectangle->getWidth()),
                static_cast<int>(rectangle->getHeight()),
                rectangle->getColor().getColor(), pc->getRotation()
            );
        }
    }

    void RenderSystem::onSceneSwitch()
    {
        if (graphicsDevice != nullptr)
            graphicsDevice->clear();
    }

    void RenderSystem::before(const float deltaTime) {}

    bool sortByLayer(DrawTexture first, DrawTexture second)
    {
        return first.layer < second.layer;
    }

    void RenderSystem::after(const float deltaTime)
    {
        drawList.sort(sortByLayer);

        for (auto texture : drawList)
        {
            graphicsDevice->drawTexture(
                texture.path,
                texture.x,
                texture.y,
                texture.w,
                texture.h,
                texture.angle,
                texture.color,
                texture.flip
            );
        }

        for (auto text : textList)
        {
            auto size = graphicsDevice->drawText(text.font, text.text, text.x, text.y, text.color, 0, biemgine::NONE, text.center);
            if(text.component != nullptr) text.component->setTextSize(size);
        }

        drawList.clear();
        textList.clear();
    }

    DrawTexture::DrawTexture(const string & path, int x, int y, int w, int h, float angle, Color color, unsigned int layer, bool center, TextureFlip flip) :
        path(path), x(x), y(y), w(w), h(h), color(color), angle(angle), layer(layer), center(center), flip(flip) {}


    DrawText::DrawText(Font pFont, const string& text, int x, int y, Color color, std::shared_ptr<TextComponent> component, bool center) :
        font(pFont),text(text), x(x), y(y), color(color), component(component), center(center) {}
}
