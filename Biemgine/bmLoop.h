#pragma once

#include "sdlWindow.h"
#include "bmInputManager.h"
#include "bmDrawable.h"
#include <vector>

class bmLoop
{
public:
	bmInputManager im;

	void start(const SdlWindow * sldwindow);
	void signalQuit();

private:
	SDL_Event event;
	SDL_Window* window = nullptr;

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



