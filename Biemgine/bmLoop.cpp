#include "stdafx.h"
#include "bmLoop.h"

void bmLoop::start(const SdlWindow* sdlwindow)
{
	if (sdlwindow->window != nullptr) {
		window = sdlwindow->window;
	}

	if (sdlwindow->renderer != nullptr) {
		renderer = sdlwindow->renderer;
	}

	created();
	startLoop();
}

void bmLoop::signalQuit()
{
	quit = true;
}

void bmLoop::startLoop()
{
	while (!quit) {

		pollEvents();
		globalUpdate();

		globalDraw();
		SDL_GL_SwapWindow(window);

	}

	globalEnd();
	end();
}

void bmLoop::pollEvents()
{
	while (SDL_PollEvent(&event)) {
		quit = event.type == SDL_QUIT;
	}
}

void bmLoop::globalUpdate()
{
	im.update();

	update();
}

void bmLoop::globalDraw()
{
	glClear(GL_COLOR_BUFFER_BIT);

	draw();

	SDL_RenderPresent(renderer);
}

void bmLoop::globalEnd()
{
	glClear(GL_COLOR_BUFFER_BIT);

	SDL_RenderPresent(renderer);
}



