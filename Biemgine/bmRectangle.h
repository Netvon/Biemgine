#pragma once
#include "bmDrawable.h"
class bmRectangle :
	public bmDrawable
{
public:
	bmRectangle(int x, int y, int width, int height) : bmDrawable(x, y, width, height) { };

	void draw() override;
	void init() override;

private:
	const GLchar* vertexSource;
	const GLchar* fragmentSource;
};

