#pragma once
#include <string>
#include "GraphicsDevice.h"

using namespace std;

class Window
{
public:
	Window
	(
		const string& title = "Untitled Window",
		const int32_t& width = 800,
		const int32_t& height = 600,
		const int32_t& options = SDL_WINDOW_SHOWN,
		const int32_t& renderOptions = SDL_RENDERER_ACCELERATED
	);

	~Window();

	GraphicsDevice* getGraphicsDevice() const;

private:
	bool init();
	void initWindow(
		const string& title,
		const int32_t& width,
		const int32_t& height,
		const int32_t& options
	);

	void initRenderer(const int32_t& renderOptions);

	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;

	SDL_GLContext glContext = nullptr;
	GraphicsDevice* gd;
};

