#pragma once
#include "bmSystem.h"
#include "bmEntity.h"
#include "GraphicsDevice.h"

class bmRenderSystem 
	: public bmSystem
{
public:
	void setGraphicsDevice(GraphicsDevice* graphicsDevice) {
		this->graphicsDevice = graphicsDevice;
	}

	void update(const bmEntity& entity) override;
	void onSceneSwitch() override;
	void before() override;

	void after() override;

private:
	GraphicsDevice* graphicsDevice;
};

