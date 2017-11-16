#include "stdafx.h"
#include "RenderSystem.h"
#include "..\components\PositionComponent.h"
#include "..\components\ColorComponent.h"
#include "..\components\RectangleComponent.h"
#include "..\components\TextureComponent.h"
#include "..\entities\Entity.h"

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

        auto pc = entity.getComponent<PositionComponent*>("position");

        if (entity.hasComponent("text")) {
            auto tx = entity.getComponent<TextComponent*>("text");

            if (tx->isVisible()) {
                textList.push_back(DrawText(
                    tx->getText(),
                    static_cast<int>(pc->getX() + tx->getOffsetX()),
                    static_cast<int>(pc->getY() + tx->getOffsetY()),
                    tx->getColor(),
                    tx
                ));
            }
        }

        if (!entity.hasComponent("texture") && !entity.hasComponent("rectangle"))
            return;

        if (entity.hasComponent("texture")) {
            auto tc = entity.getComponents<TextureComponent*>("texture");
            auto cc = entity.getComponent<ColorComponent*>("color");            

            for (auto tex : tc) {
                if (!tex->isVisible()) continue;

                drawList.push_back(DrawTexture(
                    tex->getPath(),
                    static_cast<int>(pc->getX() + tex->getOffsetX()),
                    static_cast<int>(pc->getY() + tex->getOffsetY()),
                    tex->getWidth(),
                    tex->getHeight(),
                    pc->getRotation(),
                    cc->getColor(),
                    tex->getLayer()
                ));
            }
        }

        if (entity.hasComponent("rectangle"))
        {
            auto rectangle = entity.getComponent<RectangleComponent*>("rectangle");

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
                texture.color
            );
        }

        for (auto text : textList)
        {
            auto size = graphicsDevice->drawText(text.text, text.x, text.y, text.color, 0);
            if(text.component != nullptr) text.component->setTextSize(size);
        }

        drawList.clear();
        textList.clear();
    }

    DrawTexture::DrawTexture(const string & path, int x, int y, int w, int h, float angle, Color color, unsigned int layer) :
        path(path), x(x), y(y), w(w), h(h), color(color), angle(angle), layer(layer) {}


    DrawText::DrawText(const string& text, int x, int y, Color color, TextComponent* component) :
        text(text), x(x), y(y), color(color), component(component) {}
}
