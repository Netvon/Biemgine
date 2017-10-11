#pragma once
#include "bmSystem.h"
#include "bmEntity.h"
#include "GraphicsDevice.h"

class bmRenderSystem 
	: public bmSystem
{
public:

	~bmRenderSystem()
	{
		cout << "Render System is being deleted" << endl;
	};

	void setGraphicsDevice(GraphicsDevice* graphicsDevice);

	void update(const bmEntity& entity) override;
	void onSceneSwitch() override;
	void before() override;

	void after() override;

private:
	GraphicsDevice* graphicsDevice = nullptr;
};

