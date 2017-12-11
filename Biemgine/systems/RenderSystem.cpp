#include "stdafx.h"
#include "RenderSystem.h"
#include "..\components\ColorComponent.h"
#include "..\components\RectangleComponent.h"
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

        
        if (cameraComponent == nullptr)
        {
            cameraComponent = entity.getComponent<CameraComponent>("camera").get();
        }

        auto pc = entity.getComponent<PositionComponent>("position");

        auto txs = entity.getComponents<TextComponent>("text");

        for (auto& tx : txs) {
            if (!tx->isVisible()) continue;

            OptDrawText opt;
            opt.textComponent = tx;
            opt.positionComponent = pc;
            opt.isUI = entity.hasComponent("ui");

            optTextList.push_back(std::move(opt));

            /*textList.push_back(DrawText(
                    tx->getFont(),
                    tx->getText(),
                    static_cast<int>(pc->getX() + tx->getOffsetX()),
                    static_cast<int>(pc->getY() + tx->getOffsetY()),
                    tx->getColor(),
                    tx,
                    tx->isCenter()
                ));*/
            
        }
        
        auto tc = entity.getComponents<TextureComponent>("texture");

        for (auto& tex : tc) {
            if (!tex->isVisible()) continue;

            OptDrawTexture opt;
            opt.textureComponent = tex;
            opt.positionComponent = pc;
            opt.isUI = entity.hasComponent("ui");

            optDrawList.push_back(std::move(opt));

            /*drawList.push_back(DrawTexture(
                tex->getPath(),
                static_cast<int>(pc->getX() + tex->getOffsetX() + deltaX),
                static_cast<int>(pc->getY() + tex->getOffsetY() + deltaY),
                tex->getWidth(),
                tex->getHeight(),
                pc->getRotation() + tex->getRotation(),
                (entity.hasComponent("color")) ? entity.getComponent<ColorComponent>("color")->getColor() : tex->getColor(),
                tex->getLayer(),
                false,
                tex->getFlip()
            ));*/

        }

        /*if (entity.hasComponent("rectangle"))
        {
            auto rectangle = entity.getComponent<RectangleComponent>("rectangle");

            graphicsDevice->drawSquare(
                static_cast<int>(pc->getX()),
                static_cast<int>(pc->getY()),
                static_cast<int>(rectangle->getWidth()),
                static_cast<int>(rectangle->getHeight()),
                rectangle->getColor().getColor(), pc->getRotation()
            );
        }*/
    }

    void RenderSystem::onSceneSwitch()
    {
        if (graphicsDevice != nullptr)
            graphicsDevice->clear();
    }

    //void RenderSystem::before(const float deltaTime) {}

    bool sortByLayer(const OptDrawTexture& first, const OptDrawTexture& second)
    {
        return first.textureComponent->getLayer() < second.textureComponent->getLayer();
    }

    void RenderSystem::after(const float deltaTime)
    {
        optDrawList.sort(sortByLayer);

        int deltaX = 0;
        int deltaY = 0;

        for (auto& texture : optDrawList)
        {
            deltaX = 0;
            deltaY = 0;

            if (cameraComponent != nullptr && !texture.isUI)
            {
                deltaX = cameraComponent->getDeltaX();
                deltaY = cameraComponent->getDeltaY();
            }

            graphicsDevice->drawTexture(
                texture.textureComponent->getPath(),
                texture.textureComponent->getOffsetX() + texture.positionComponent->getOriginX() + deltaX,
                texture.textureComponent->getOffsetY() + texture.positionComponent->getOriginY() + deltaY,
                texture.textureComponent->getWidth(),
                texture.textureComponent->getHeight(),
                texture.textureComponent->getRotation() + texture.positionComponent->getRotation(),
                texture.textureComponent->getColor(),
                texture.textureComponent->getFlip()
            );
        }
        /*printf("Drawing %llu textures\n", drawList.size());*/

        /*drawList.sort(sortByLayer);
        for (auto& texture : drawList)
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
        }*/

        for (auto& text : optTextList)
        {
            deltaX = 0;
            deltaY = 0;

            if (cameraComponent != nullptr && !text.isUI)
            {
                deltaX = cameraComponent->getDeltaX();
                deltaY = cameraComponent->getDeltaY();
            }

            auto size = graphicsDevice->drawText(
                text.textComponent->getFont(),
                text.textComponent->getText(),
                text.textComponent->getOffsetX() + text.positionComponent->getX() + deltaX,
                text.textComponent->getOffsetY() + text.positionComponent->getY() + deltaY,
                text.textComponent->getColor(),
                0,
                biemgine::NONE,
                text.textComponent->isCenter()
            );

            //auto size = graphicsDevice->drawText(text.font, text.text, text.x, text.y, text.color, 0, biemgine::NONE, text.center);
            text.textComponent->setTextSize(size);
        }


        optDrawList.clear();
        optTextList.clear();
        //drawList.clear();
        //textList.clear();
    }

    DrawTexture::DrawTexture(const string & path, int x, int y, int w, int h, float angle, Color color, unsigned int layer, bool center, TextureFlip flip) :
        path(path), x(x), y(y), w(w), h(h), color(color), angle(angle), layer(layer), center(center), flip(flip) {}


    DrawText::DrawText(Font pFont, const string& text, int x, int y, Color color, std::shared_ptr<TextComponent> component, bool center) :
        font(pFont),text(text), x(x), y(y), color(color), component(component), center(center) {}
}
