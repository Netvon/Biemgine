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

	if (!entity.hasComponent("texture") && !entity.hasComponent("rectangle")) 
		return;


    // Get the components
    // std::map<std::string, bmComponent*> componentHM = entity->getComponentHM();
    auto pc = entity.getComponent<bmPositionComponent*>("position");
    // Check if the entity has the right components
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
