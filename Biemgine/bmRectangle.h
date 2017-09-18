#pragma once
#include "bmComponent.h"
class bmRectangle :
	public bmComponent
{
public:
	bmRectangle(int x, int y, int width, int height) : bmComponent(x, y, width, height) { };

	void draw(SDL_Renderer* renderer) override;
	void init() override;

private:
	const GLchar* vertexSource;
	const GLchar* fragmentSource;
};

