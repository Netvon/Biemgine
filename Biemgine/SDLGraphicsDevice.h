#pragma once
#include "GraphicsDevice.h"

#include <map>

class SDLGraphicsDevice :
	public GraphicsDevice
{
public:
	SDLGraphicsDevice(SDL_Window* window);

	void drawSquare(int x, int y, int w, int h, bmColor color, float angle = 0) const override;
	void drawTexture(std::string path, int x, int y, int w = -1, int h = -1, float angle = 0, bmColor color = { 255, 255, 255 }, TextureFlip flip = NONE) override;
	void clear() const override;
	void present() const override;

	void destroy() override;

private:
	SDL_Renderer* renderer = nullptr;

	std::map<std::string, SDL_Texture*> textures;

	SDL_Texture* getTexture(std::string path);

};
