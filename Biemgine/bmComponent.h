#pragma once

class bmComponent
{
public:
	bmComponent(int x, int y, int width, int height);
	~bmComponent();

public:
	int x, y;
	int width, height;

	virtual void init() { };
	virtual void draw(SDL_Renderer* renderer) { };
};

