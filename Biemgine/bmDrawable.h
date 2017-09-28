#pragma once

class bmDrawable
{
public:
	bmDrawable(int x, int y, int width, int height);

public:
	int x, y;
	int width, height;

	virtual void init() { };
	virtual void draw() { };
	virtual void clear() { };
};

