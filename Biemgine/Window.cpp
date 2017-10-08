#include "stdafx.h"
#include "Window.h"
#include "SDLGraphicsDevice.h"

Window::Window(
	const string & title,
	const int32_t & width,
	const int32_t & height,
	const int32_t& options,
	const int32_t& renderOptions)
{
	if (init()) {

		initWindow(title, width, height, options);
		//initRenderer(renderOptions);

		gd = new SDLGraphicsDevice(window);
	}
}

Window::~Window()
{
	//SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	if (gd != nullptr) {
		gd->destroy();
		delete gd;
	}

	SDL_Quit();
}

GraphicsDevice * Window::getGraphicsDevice() const
{
	return gd;
}

bool Window::init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cout << "could not initialize SDL2 \n" << SDL_GetError() << "\n";
		return false;
	}

	return true;
}

void Window::initWindow(
	const string & title,
	const int32_t & width,
	const int32_t & height,
	const int32_t & options)
{
	window = SDL_CreateWindow(
		(const char*)title.c_str(),
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		width,
		height,
		options
	);

	if (window == nullptr)
		std::cout << "Failed to initialize Window\n" << SDL_GetError() << "\n";
}

//void Window::initRenderer(
//	const int32_t & renderOptions)
//{
//	renderer = SDL_CreateRenderer(
//		window, -1, renderOptions
//	);
//
//	if (renderer == nullptr)
//		std::cout << "Failed to initialize Renderer\n" << SDL_GetError() << "\n";
//}
