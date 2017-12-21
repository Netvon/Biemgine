#include "stdafx.h"
#include "RenderSystem.h"
#include "..\components\ColorComponent.h"
#include "..\components\RectangleComponent.h"
#include "..\entities\Entity.h"
#include "..\devices\graphics\TextureFlip.h"
#include "..\components\AnimatedTextureComponent.h"

namespace biemgine
{
    RenderSystem::~RenderSystem() {}
 
    void RenderSystem::setGraphicsDevice(GraphicsDevice* graphicsDevice)
    {
        this->graphicsDevice = graphicsDevice;
    }


    bool sortByLayer(const OptDrawTexture& first, const OptDrawTexture& second)
    {
        return first.textureComponent->getLayer() < second.textureComponent->getLayer();
    }

    void RenderSystem::onAddEntity(Entity & entity)
    {
        if (!cameraComponent)
        {
            cameraComponent = entity.getComponent<CameraComponent>("camera");
        }

        auto pc = entity.getComponent<PositionComponent>("position");
        if (pc == nullptr)
        {
            return;
        }
           
        auto txs = entity.getComponents<TextComponent>("text");

        for (auto tx : txs)
        {
            OptDrawText opt;
            opt.entity = &entity;
            opt.textComponent = tx;
            opt.positionComponent = pc;
            opt.isUI = entity.hasComponent("ui");

            optTextList.push_back(std::move(opt));
        }

        auto tc = entity.getComponents<TextureComponent>("texture");

        for (auto tex : tc)
        {
            OptDrawTexture opt;
            opt.entity = &entity;
            opt.textureComponent = tex;
            opt.positionComponent = pc;
            opt.isUI = entity.hasComponent("ui");

            optDrawList.push_back(std::move(opt));
        }

        optDrawList.sort(sortByLayer);
    }

    void RenderSystem::update(const float deltaTime)
    {
        int deltaX = 0;
        int deltaY = 0;

        for (auto texture : optDrawList)
        {
            if (!texture.textureComponent->isVisible() || !texture.entity->isAlive() || !texture.entity->getIsOnScreen()) continue;
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
                texture.textureComponent->getFlip(),
                false,
                texture.textureComponent->getRect()
            );

            texture.textureComponent->update(deltaTime);
        }

        for (auto text : optTextList)
        {
            if (!text.textComponent->isVisible() || !text.entity->isAlive() || !text.entity->getIsOnScreen()) continue;

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

            text.textComponent->setTextSize(size);
        }
    }

    void RenderSystem::onSceneSwitch()
    {
        if (graphicsDevice != nullptr)
            graphicsDevice->clear();
    }
}
