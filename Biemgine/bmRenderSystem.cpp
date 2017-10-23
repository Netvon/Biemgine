#include "stdafx.h"
#include "bmRenderSystem.h"
#include "bmPositionComponent.h"
#include "bmColorComponent.h"
#include "bmRectangleComponent.h"
#include "bmTextureComponent.h"
#include "bmAtmosphereComponent.h"
#include "bmGravityComponent.h"
#include "bmEntity.h"


void bmRenderSystem::setGraphicsDevice(GraphicsDevice* graphicsDevice)
{
    this->graphicsDevice = graphicsDevice;
}

void bmRenderSystem::update(const bmEntity& entity, const float deltaTime)
{
    if (!entity.hasComponent("position"))
        return;

    auto pc = entity.getComponent<bmPositionComponent*>("position");

    if (entity.hasComponent("text")) {
        auto tx = entity.getComponent<bmTextComponent*>("text");
        graphicsDevice->drawText(tx->getText(), pc->getX(), pc->getY(), { 255,255,255,255 }, 0);
    }

	if (!entity.hasComponent("texture") && !entity.hasComponent("rectangle")) 
		return;


    if (entity.hasComponent("texture")) {
        auto cc = entity.getComponent<bmColorComponent*>("color");

        auto tc = entity.getComponents<bmTextureComponent*>("texture");

        for (auto tex : tc) {
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
    else {
        auto rectangle = entity.getComponent<bmRectangleComponent*>("rectangle");

        graphicsDevice->drawSquare(
            static_cast<int>(pc->getX()),
            static_cast<int>(pc->getY()),
            static_cast<int>(rectangle->getWidth()),
            static_cast<int>(rectangle->getHeight()),
            rectangle->getColor().getColor(), pc->getRotation()
        );
    }

    // Parse the base component to the right derived component
    //bmPositionComponent* pc = dynamic_cast<bmPositionComponent*>(componentHM["position"]);

    // Action!
    //std::cout << "Rendering id:" << entity.getId() << " at x:" << pc->getX() << " and y:" << pc->getY() << std::endl;

    /*float offsetX = static_cast<float>(rand() % 2) / 10.0;
    float offsetY = static_cast<float>(rand() % 2) / 10.0;

    pc->add(offsetX, offsetY);*/

    float angle = 0;//static_cast<float>(rand() % 360);
    // bmColor color = { rand() % 255, rand() % 255, rand() % 255 };

    //graphicsDevice->drawSquare(pc->getX(), pc->getY(), 50, 50, cc->getColor());
    //graphicsDevice->drawTexture("../../Biemgine/textures/biemlogo.png", pc->getX(), pc->getY(), 100, 56);

}

void bmRenderSystem::onSceneSwitch()
{
    if (graphicsDevice != nullptr)
        graphicsDevice->clear();
}

void bmRenderSystem::before(const float deltaTime)
{
}

bool sortByLayer(DrawTexture first, DrawTexture second)
{
    return first.layer < second.layer;
}

void bmRenderSystem::after(const float deltaTime)
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


    drawList.clear();
}
