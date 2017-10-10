#include "stdafx.h"
#include "SDLGraphicsDevice.h"

#include <SDL_image.h>

SDLGraphicsDevice::SDLGraphicsDevice(SDL_Window * window)
{
    textures = new std::map<std::string, SDL_Texture*>();
	renderer = SDL_CreateRenderer(window, -1, 0);

	if (IMG_Init(IMG_INIT_PNG) == 0) {
		std::cout << IMG_GetError() << std::endl;
	}

	SDL_Rect viewport = { 0, 0, 0, 0 };

	SDL_GetWindowSize(window, &viewport.w, &viewport.h);
	SDL_RenderSetViewport(renderer, &viewport);
}

void SDLGraphicsDevice::destroy()
{
	/*for (std::pair<std::string, SDL_Surface*> pair : surfaces) {
		SDL_FreeSurface(pair.second);
	}

	surfaces.clear();*/

	for (std::pair<std::string, SDL_Texture*> pair : *textures) {
		SDL_DestroyTexture(pair.second);
	}

	textures->clear();


	if (renderer != nullptr) {
		SDL_DestroyRenderer(renderer);
	}

	IMG_Quit();

    delete textures;

	
}

void SDLGraphicsDevice::drawSquare(int x, int y, int w, int h, bmColor color, float angle) const
{
	/*SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);*/

	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_Rect rect = { x, y, w, h };

	SDL_RenderFillRect(renderer, &rect);
}

void SDLGraphicsDevice::drawTexture(std::string path, int x, int y, int w, int h, float angle, bmColor color, TextureFlip flip)
{
	auto texture = getTexture(path);

	if (texture != nullptr) {
		if (w == -1 && h == -1) {
			SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);
		}

		SDL_Rect rec = { x, y, w, h };

		SDL_SetTextureColorMod(texture, color.r, color.g, color.b);
		
		SDL_RenderCopyEx(renderer, texture, nullptr, &rec, angle, nullptr, static_cast<SDL_RendererFlip>(flip));
		
	}
}

void SDLGraphicsDevice::clear() const
{
	if (renderer != nullptr) {
		SDL_SetRenderDrawColor(renderer, 100, 149, 237, 255);
		SDL_RenderClear(renderer);
	}
}

void SDLGraphicsDevice::present() const
{
	SDL_RenderPresent(renderer);
}

SDL_Texture * SDLGraphicsDevice::getTexture(std::string path)
{
	if (textures->find(path) != textures->end()) {
		return textures->at(path);
	}

	SDL_Surface* surface = IMG_Load(path.c_str());

	//auto err = IMG_GetError();

	if (surface != nullptr) {
		// SDL_Surface* texture = SDL_ConvertSurfaceFormat(surface, SDL_PIXELFORMAT_ABGR8888, 0);

		if (surface != nullptr) {
			//SDL_FreeSurface(texture);

			auto tex = SDL_CreateTextureFromSurface(renderer, surface);
			textures->insert_or_assign(path, tex);

			//SDL_FreeSurface(texture);
			SDL_FreeSurface(surface);

			return tex;
		}
		
	}

	return nullptr;
}
