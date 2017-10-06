#pragma once
#include "bmColor.h"

class GraphicsDevice
{
public:
	virtual void drawSquare(int x, int y, int w, int h, bmColor color, float angle = 0) const = 0;
	virtual void clear() const = 0;
	virtual void present() const = 0;
};