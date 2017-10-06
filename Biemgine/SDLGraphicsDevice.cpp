#include "stdafx.h"
#include "SDLGraphicsDevice.h"

SDLGraphicsDevice::SDLGraphicsDevice(SDL_Window * window)
{
	this->window = window;
	renderer = SDL_CreateRenderer(window, -1, 0);
}

SDLGraphicsDevice::~SDLGraphicsDevice()
{
	if (renderer != nullptr) {
		SDL_DestroyRenderer(renderer);
		delete renderer;
	}
}

void SDLGraphicsDevice::drawSquare(int x, int y, int w, int h, bmColor color, float angle) const
{
	/*SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);*/

	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_Rect rect = { x, y, w, h };

	SDL_RenderFillRect(renderer, &rect);
}

void SDLGraphicsDevice::clear() const
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
}

void SDLGraphicsDevice::present() const
{
	SDL_RenderPresent(renderer);
}

SDL_Texture * SDLGraphicsDevice::getTexture(string path)
{
	
}
