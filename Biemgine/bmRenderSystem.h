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

	void update(const bmEntity& entity, const float deltaTime) override;
	void onSceneSwitch() override;
	void before(const float deltaTime) override;
	void after(const float deltaTime) override;

private:
	GraphicsDevice* graphicsDevice = nullptr;
};

