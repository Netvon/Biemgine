#pragma once

#include "sdlWindow.h"
#include "bmInputManager.h"
#include "bmDrawable.h"
#include <vector>

class bmLoop
{
public:
	SDL_Event event;
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;

	bmInputManager im;

	void start(const SdlWindow * sldwindow);
	void signalQuit();

private:
	bool quit = false;

	void startLoop();
	void pollEvents();

	void globalUpdate();
	void globalDraw();
	void globalEnd();

	virtual void update() { }
	virtual void draw() { }
	virtual void created() { }
	virtual void end() { }
};

