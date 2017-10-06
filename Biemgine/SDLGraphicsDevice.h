#pragma once
#include "GraphicsDevice.h"

#include <vector>

using namespace std;

class SDLGraphicsDevice :
	public GraphicsDevice
{
public:
	SDLGraphicsDevice(SDL_Window* window);
	~SDLGraphicsDevice();

	void drawSquare(int x, int y, int w, int h, bmColor color, float angle = 0) const override;
	void clear() const override;
	void present() const override;

	SDL_Texture* getTexture(string path);

private:
	SDL_Window* window;
	SDL_Renderer* renderer;

	vector<string, SDL_Texture*> textures;

};

