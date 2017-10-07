#pragma once
#include "bmColor.h"

#include <string>

using namespace std;

class GraphicsDevice
{
public:
	virtual void drawSquare(int x, int y, int w, int h, bmColor color, float angle = 0) const = 0;
	virtual void drawTexture(string path, int x, int y, int w, int h, float angle = 0, bmColor color = { 255, 255, 255 }) = 0;
	virtual void clear() const = 0;
	virtual void present() const = 0;
};