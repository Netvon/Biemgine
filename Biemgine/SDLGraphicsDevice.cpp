#include "stdafx.h"
#include "SDLGraphicsDevice.h"
#include <SDL_ttf.h>
#include <SDL_image.h>

SDLGraphicsDevice::SDLGraphicsDevice(SDL_Window * window)
{
    renderer = SDL_CreateRenderer(window, -1, 0);

    if (IMG_Init(IMG_INIT_PNG) == 0) {
        std::cout << IMG_GetError() << std::endl;
    }

    if (TTF_Init() < 0) {
        std::cout << TTF_GetError() << std::endl;
    }

    font = TTF_OpenFont("consolas.ttf", 20);

	SDL_Rect viewport = { 0, 0, 0, 0 };

    SDL_GetWindowSize(window, &viewport.w, &viewport.h);
    SDL_RenderSetViewport(renderer, &viewport);
    //SDL_RenderSetScale(renderer, 2.f, 2.f);
}

SDLGraphicsDevice::~SDLGraphicsDevice()
{
    /*for (std::pair<std::string, SDL_Surface*> pair : surfaces) {
    SDL_FreeSurface(pair.second);
    }

    surfaces.clear();*/

    for (std::pair<std::string, SDL_Texture*> pair : textures) {
        SDL_DestroyTexture(pair.second);
    }

    textures.clear();

    if (renderer != nullptr) {
        SDL_DestroyRenderer(renderer);
    }

    TTF_CloseFont(font);

    TTF_Quit();
	IMG_Quit();
}

void SDLGraphicsDevice::drawSquare(int x, int y, int w, int h, bmColor color, float angle) const
{
    /*SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);*/

    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_Rect rect = { x, y, w, h };

    SDL_RenderFillRect(renderer, &rect);
}

void SDLGraphicsDevice::drawText(std::string text, int x, int y, bmColor color, int ptSize) {

    SDL_Color convertedColor = { color.r, color.g, color.b, color.a };
    SDL_Surface *textSurface = TTF_RenderText_Solid(font, text.c_str(), convertedColor);
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

    SDL_Rect textRect = { x, y };

    SDL_QueryTexture(textTexture, nullptr, nullptr, &textRect.w, &textRect.h);

    SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);

    SDL_FreeSurface(textSurface);

    // TODO: Destory texture
    SDL_DestroyTexture(textTexture);
}

void SDLGraphicsDevice::drawTexture(std::string path, int x, int y, int w, int h, float angle, bmColor color, TextureFlip flip)
{
    auto texture = getTexture(path);

    if (texture != nullptr) {
        if (w == -1 && h == -1) {
            SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);
        }

        SDL_Rect rec = { x, y, w, h };
        SDL_Point center = { 0,0 };

        SDL_SetTextureColorMod(texture, color.r, color.g, color.b);
        
        SDL_RenderCopyEx(renderer, texture, nullptr, &rec, angle, &center, static_cast<SDL_RendererFlip>(flip));
        
    }
}

void SDLGraphicsDevice::clear() const
{
    if (renderer != nullptr) {
        //SDL_SetRenderDrawColor(renderer, 100, 149, 237, 255);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
    }
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

    SDL_Surface* surface = IMG_Load(path.c_str());

    //auto err = IMG_GetError();

    if (surface != nullptr) {
        // SDL_Surface* texture = SDL_ConvertSurfaceFormat(surface, SDL_PIXELFORMAT_ABGR8888, 0);

        if (surface != nullptr) {
            //SDL_FreeSurface(texture);

            auto tex = SDL_CreateTextureFromSurface(renderer, surface);
            textures.insert_or_assign(path, tex);

            //SDL_FreeSurface(texture);
            SDL_FreeSurface(surface);

            return tex;
        }
        
    }

    return nullptr;
}
