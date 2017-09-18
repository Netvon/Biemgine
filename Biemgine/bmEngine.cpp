#include "stdafx.h"
#include "bmEngine.h"
#include "bmPlanetScene.h"
#include "sdlWindow.h"

bmEngine::bmEngine()
{
	SdlWindow window(
		"Biem Test 01",
		800, 600,
		SDL_WINDOW_OPENGL,
		SDL_RENDERER_ACCELERATED
	);

	bmPlanetScene loop;
	loop.start(window);
}

//bool bmEngine::init()
//{
//	if (SDL_Init(SDL_INIT_VIDEO) < 0)
//	{
//		printf("SDL Init failed");
//		return false;
//	}
//	else
//	{
//		window = SDL_CreateWindow("Biem Test 01", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
//	
//		if (window == nullptr)
//		{
//			printf("SDL Window Init failed");
//			return false;
//		}
//		else
//		{
//			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
//
//			if (window == nullptr)
//			{
//				printf("SDL renderer Init failed");
//				return false;
//			}
//			else
//			{
//				SDL_UpdateWindowSurface(window);
//			}
//		}
//	}
//
//	return true;
//}
//
//void bmEngine::start()
//{
//	if (init()) 
//	{
//		while (run) 
//		{
//			update();
//			draw();
//		}
//	}
//}
//
//void bmEngine::update()
//{
//	// update logic here
//
//	SDL_Delay(12);
//}
//
//void bmEngine::draw()
//{
//	SDL_SetRenderDrawColor(renderer, 0x93, 0xCC, 0xEA, 0xFF);
//	SDL_RenderClear(renderer);
//
//	// draw here
//
//	SDL_Rect rect { 0, 0, 100, 100 };
//
//	SDL_SetRenderDrawColor(renderer, 0xFF, 0, 0, 255);
//	SDL_RenderFillRect(renderer, &rect);
//
//	SDL_RenderPresent(renderer);
//}