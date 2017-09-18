#include "stdafx.h"
#include "sdlWindow.h"

SdlWindow::SdlWindow(
	const string & title,
	const int32_t & width,
	const int32_t & height,
	const int32_t& options,
	const int32_t& renderOptions)
{
	if (initSdl()) {

		initWindow(title, width, height, options);
		 
		if ((renderOptions & SDL_WINDOW_OPENGL) == 0) {
			initRenderer(renderOptions);
		}
	}
}

SdlWindow::~SdlWindow()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	if (glContext != nullptr) {
		SDL_GL_DeleteContext(glContext);
	}

	SDL_Quit();
}

bool SdlWindow::initSdl()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cout << "could not initialize SDL2 \n" << SDL_GetError() << "\n";
		return false;
	}

	return true;
}

SdlWindow & SdlWindow::initWindow(
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
	else {
		if ((options & SDL_WINDOW_OPENGL) == SDL_WINDOW_OPENGL) {
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
			SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

			glContext = SDL_GL_CreateContext(window);

			SDL_GL_SetSwapInterval(0);

			if (glContext != nullptr) {
				glewExperimental = GL_TRUE;
				glewInit();

				GLuint vertexBuffer;
				glGenBuffers(1, &vertexBuffer);

				printf("%s\n", glGetString(GL_VERSION));
			}
		}
	}

	return *this;
}

SdlWindow & SdlWindow::initRenderer(
	const int32_t & renderOptions)
{
	renderer = SDL_CreateRenderer(
		window, -1, renderOptions
	);

	if (renderer == nullptr)
		std::cout << "Failed to initialize Renderer\n" << SDL_GetError() << "\n";

	return *this;
}
