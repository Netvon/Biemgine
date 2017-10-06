#include "stdafx.h"
#include "bmLoop.h"

void bmLoop::start(const Window* bmwindow)
{
	window = bmwindow;

	created();
	startLoop();
}

void bmLoop::signalQuit()
{
	quit = true;
}

void bmLoop::updateDeltaTime()
{
	float currentFrame = static_cast<float>(SDL_GetTicks());
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
}

void bmLoop::startLoop()
{
	while (!quit) {

		updateDeltaTime();

		pollEvents();
		globalUpdate();

		//globalDraw();

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

	update(deltaTime);
}

//void bmLoop::globalDraw()
//{
//	glClear(GL_COLOR_BUFFER_BIT);
//
//	draw();
//}

void bmLoop::globalEnd()
{
	//glClear(GL_COLOR_BUFFER_BIT);
}



