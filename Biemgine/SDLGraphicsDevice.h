#pragma once
#include "GraphicsDevice.h"

#include <map>

class SDLGraphicsDevice :
	public GraphicsDevice
{
public:
	SDLGraphicsDevice(SDL_Window* window);
	~SDLGraphicsDevice();

	void drawSquare(int x, int y, int w, int h, bmColor color, float angle = 0) const override;
	void drawTexture(std::string path, int x, int y, int w, int h, float angle = 0, bmColor color = { 255, 255, 255 }) override;
	void clear() const override;
	void present() const override;

	

private:
	SDL_Window* window;
	SDL_Renderer* renderer;

	map<string, SDL_Texture*> textures;
	map<string, SDL_Surface*> surfaces;

	SDL_Texture* getTexture(std::string path);
	SDL_Surface* getSurface(std::string path);

};

