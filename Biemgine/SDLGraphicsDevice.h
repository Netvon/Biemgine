#pragma once

#include "GraphicsDevice.h"
#include <SDL_ttf.h>
#include "TextureAndUsage.h"
#include <map>

class SDLGraphicsDevice :
    public GraphicsDevice
{
public:

    SDLGraphicsDevice(SDL_Window* window);
    ~SDLGraphicsDevice();

	void drawSquare(int x, int y, int w, int h, bmColor color, float angle = 0) const override;
	void drawTexture(std::string path, int x, int y, int w = -1, int h = -1, float angle = 0, bmColor color = { 255, 255, 255 }, TextureFlip flip = NONE) override;
    void drawText(std::string text, int x, int y, bmColor color, int ptSize, TextureFlip flip = NONE) override;
    void clear() const override;
	void present() override;

private:

	SDL_Renderer* renderer = nullptr;
    TTF_Font* font = nullptr;

	std::map<std::string, SDL_Texture*> textures;
    std::map<std::string, TextureAndUsage> textTextures;

    SDL_Texture* getTexture(std::string path);

};
