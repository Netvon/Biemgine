#pragma once
#include "bmColor.h"
#include "TextureFlip.h"

#include <string>

class GraphicsDevice
{
public:
	virtual void drawSquare(int x, int y, int w, int h, bmColor color, float angle = 0) const = 0;
	virtual void drawTexture(std::string path, int x, int y, int w = -1, int h = -1, float angle = 0, bmColor color = { 255, 255, 255 }, TextureFlip flip = NONE) = 0;
	
	virtual void clear() const = 0;
	virtual void present() const = 0;

	virtual void destroy() = 0;
};