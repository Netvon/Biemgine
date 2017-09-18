#pragma once
#include <string>
#include "bmColor.h"

using namespace std;

class SdlWindow
{
public:
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;

	SDL_GLContext glContext = nullptr;

	SdlWindow
	(
		const string& title = "Untitled Window",
		const int32_t& width = 800,
		const int32_t& height = 600,
		const int32_t& options = SDL_WINDOW_SHOWN,
		const int32_t& renderOptions = SDL_RENDERER_ACCELERATED
	);

	~SdlWindow();

private:
	bool initSdl();
	SdlWindow& initWindow(
		const string& title,
		const int32_t& width,
		const int32_t& height,
		const int32_t& options
	);
	SdlWindow& initRenderer(const int32_t& renderOptions);
};

