#include "stdafx.h"
#include "SDLGraphicsDevice.h"

#include <SDL_ttf.h>
#include <SDL_image.h>

namespace biemgine {

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
        //SDL_RenderSetScale(renderer, 0.25f, 0.25f);

        SDL_RenderSetLogicalSize(renderer, 1920, 1080);

        SDL_MaximizeWindow(window);
    }

    SDLGraphicsDevice::~SDLGraphicsDevice()
    {
        for (std::pair<std::string, TextureAndUsage> pair : textTextures) {
            SDL_DestroyTexture(pair.second.texture);
        }

        textures.clear();
        textTextures.clear();

        if (renderer != nullptr) {
            SDL_DestroyRenderer(renderer);
        }

        TTF_CloseFont(font);

        TTF_Quit();
        IMG_Quit();
    }

    void SDLGraphicsDevice::drawSquare(int x, int y, int w, int h, Color color, float angle) const
    {
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        SDL_Rect rect = { x, y, w, h };

        SDL_RenderFillRect(renderer, &rect);
    }

    Size SDLGraphicsDevice::drawText(const std::string& text, int x, int y, Color color, int ptSize, TextureFlip flip) {

        if (textTextures.find(text) == textTextures.end()) {
            SDL_Color convertedColor = { color.r, color.g, color.b, color.a };
            SDL_Surface *textSurface = TTF_RenderText_Blended(font, text.c_str(), convertedColor);
            SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

            SDL_FreeSurface(textSurface);

            TextureAndUsage textureAndUsage = { textTexture, 0 };
            textTextures.insert_or_assign(text, textureAndUsage);
        }

        TextureAndUsage &textFromKey = textTextures.at(text);
        textFromKey.usageCount++;

        SDL_Rect textRect = { x, y };

        SDL_QueryTexture(textFromKey.texture, nullptr, nullptr, &textRect.w, &textRect.h);

        SDL_RenderCopyEx(renderer, textFromKey.texture, nullptr, &textRect, 0, nullptr, static_cast<SDL_RendererFlip>(flip));

        return { textRect.w, textRect.h };
    }

    void SDLGraphicsDevice::drawTexture(const std::string& path, int x, int y, int w, int h, float angle, Color color, TextureFlip flip)
    {
        auto texture = getTexture(path);

        if (texture != nullptr) {
            if (w == -1 && h == -1) {
                SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);
            }

            SDL_Rect rec = { x, y, w, h };
            SDL_Point center = { 0,0 };

            SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
            SDL_SetTextureAlphaMod(texture, color.a);

            SDL_SetTextureColorMod(texture, color.r, color.g, color.b);

            SDL_RenderCopyEx(renderer, texture, nullptr, &rec, static_cast<double>(angle), nullptr, static_cast<SDL_RendererFlip>(flip));

        }
    }

    void SDLGraphicsDevice::clear() const
    {
        if (renderer != nullptr) {
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);
        }
    }

    void SDLGraphicsDevice::present()
    {
        SDL_RenderPresent(renderer);

        for (auto it = textTextures.begin(); it != textTextures.end();)
        {
            it->second.usageCount--;

            if (it->second.usageCount < 0)
            {
                SDL_DestroyTexture(it->second.texture);
                it = textTextures.erase(it);
            }
            else
            {
                ++it;
            }
        }
    }

    SDL_Texture * SDLGraphicsDevice::getTexture(std::string path)
    {
        if (textures.find(path) != textures.end()) {
            return textures.at(path);
        }

        SDL_Surface* surface = IMG_Load(path.c_str());


        if (surface != nullptr) {
            auto tex = SDL_CreateTextureFromSurface(renderer, surface);

            textures.insert_or_assign(path, tex);

            SDL_FreeSurface(surface);

            return tex;
        }

        return nullptr;
    }
}
