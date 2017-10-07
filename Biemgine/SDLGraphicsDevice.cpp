#include "stdafx.h"
#include "SDLGraphicsDevice.h"

#include <SDL_image.h>

SDLGraphicsDevice::SDLGraphicsDevice(SDL_Window * window)
{
	this->window = window;
	renderer = SDL_CreateRenderer(window, -1, 0);
}

SDLGraphicsDevice::~SDLGraphicsDevice()
{
	if (renderer != nullptr) {
		SDL_DestroyRenderer(renderer);
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

void SDLGraphicsDevice::drawTexture(std::string path, int x, int y, int w, int h, float angle, bmColor color)
{
	auto texture = getTexture(path);

	if (texture != nullptr) {
		SDL_Rect rec = { x, y, w, h };

		SDL_SetTextureColorMod(texture, color.r, color.g, color.b);

		//SDL_RenderCopy(renderer, texture, nullptr, &rec);
		SDL_RenderCopyEx(renderer, texture, nullptr, &rec, angle, nullptr, SDL_FLIP_NONE);
		
	}
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

SDL_Texture * SDLGraphicsDevice::getTexture(std::string path)
{
	if (textures.find(path) != textures.end()) {
		return textures.at(path);
	}

	auto surface = getSurface(path);

	if (surface != nullptr) {
		auto tex = SDL_CreateTextureFromSurface(renderer, surface);

		textures.insert_or_assign(path, tex);

		SDL_FreeSurface(surface);

		return tex;
	}
}

SDL_Surface * SDLGraphicsDevice::getSurface(std::string path)
{
	if (surfaces.find(path) != surfaces.end()) {
		return surfaces.at(path);
	}

	SDL_Surface* surface = nullptr;
	surface = IMG_Load(path.c_str());

	auto err = IMG_GetError();

	if (surface != nullptr) {
		SDL_Surface* texture = SDL_ConvertSurfaceFormat(surface, SDL_PIXELFORMAT_ABGR8888, 0);

		if (texture != nullptr) {
			//SDL_FreeSurface(texture);

			surfaces.insert_or_assign(path, texture);
			return texture;
		}

		surfaces.insert_or_assign(path, surface);
		return surface;
	}

	return nullptr;
}
