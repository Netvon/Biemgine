#include "stdafx.h"
#include "bmLoop.h"

void bmLoop::start(const SdlWindow & sdlwindow)
{
	if (sdlwindow.window != nullptr) {
		window = sdlwindow.window;
	}

	if (sdlwindow.renderer != nullptr) {
		renderer = sdlwindow.renderer;
	}

	created();
	startLoop();
}

void bmLoop::signalQuit()
{
	quit = true;
}

//void bmLoop::addComponent(bmComponent * newComponent)
//{
//	components.push_back(newComponent);
//}

void bmLoop::startLoop()
{
	while (!quit) {

		pollEvents();

		globalUpdate();
		globalDraw();

		SDL_GL_SwapWindow(window);
	}

	end();
	//globalEnd();
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
	SDL_SetRenderDrawColor(renderer, 0x93, 0xCC, 0xEA, 0xFF);
	SDL_RenderClear(renderer);

	//drawComponents();
	draw();

	SDL_RenderPresent(renderer);
}

//void bmLoop::drawComponents()
//{
//	for (auto* c : components) {
//		c->draw(renderer);
//	}
//}

