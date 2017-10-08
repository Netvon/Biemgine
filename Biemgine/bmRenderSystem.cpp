#include "stdafx.h"
#include "bmRenderSystem.h"
#include "bmPositionComponent.h"
#include "bmColorComponent.h"
#include "bmTextureComponent.h"
#include "bmEntity.h"


void bmRenderSystem::setGraphicsDevice(GraphicsDevice* graphicsDevice) 
{
	this->graphicsDevice = graphicsDevice;
}

void bmRenderSystem::update(const bmEntity& entity) {

	// Get the components
	// std::map<std::string, bmComponent*> componentHM = entity->getComponentHM();
	auto pc = entity.getComponent<bmPositionComponent*>("position");
	auto cc = entity.getComponent<bmColorComponent*>("color");
	auto tc = entity.getComponent<bmTextureComponent*>("texture");

	// Check if the entity has the right components
	if (entity.hasComponent("position"))
		return;

	// Parse the base component to the right derived component
	//bmPositionComponent* pc = dynamic_cast<bmPositionComponent*>(componentHM["position"]);
	

	// Action!
	std::cout << "Rendering id:" << entity.getId() << " at x:" << pc->getX() << " and y:" << pc->getY() << std::endl;

	/*float offsetX = static_cast<float>(rand() % 2) / 10.0;
	float offsetY = static_cast<float>(rand() % 2) / 10.0;

	pc->add(offsetX, offsetY);*/

	float angle = 0;//static_cast<float>(rand() % 360);
	// bmColor color = { rand() % 255, rand() % 255, rand() % 255 };

	//graphicsDevice->drawSquare(pc->getX(), pc->getY(), 50, 50, cc->getColor());
	//graphicsDevice->drawTexture("../../Biemgine/textures/biemlogo.png", pc->getX(), pc->getY(), 100, 56);
	graphicsDevice->drawTexture(
		tc->getPath(),
		static_cast<int>(pc->getX()),
		static_cast<int>(pc->getY())
	);
}

void bmRenderSystem::onSceneSwitch()
{
	if(graphicsDevice != nullptr)
		graphicsDevice->clear();
}

void bmRenderSystem::before()
{
	graphicsDevice->clear();
}

void bmRenderSystem::after()
{
	graphicsDevice->present();
}

void bmRenderSystem::destroy()
{
	//graphicsDevice->destroy();
}
