#pragma once

#include "Window.h"
#include "bmInputManager.h"
#include <vector>

class bmLoop
{
public:
	bmInputManager im;

	virtual ~bmLoop() {};

	void start(const Window * window);
	void signalQuit();

	const Window* getWindow() const {
		return window;
	}

private:
	SDL_Event event;
	const Window* window;

	bool quit = false;

	float deltaTime = 0.0f;
	float lastFrame = 0.0f;

	void updateDeltaTime();

	void startLoop();
	void pollEvents();

	void globalUpdate();
	//void globalDraw();
	void globalEnd();

	virtual void update(float deltaTime) { }
	virtual void created() { }
	virtual void end() { }
};



