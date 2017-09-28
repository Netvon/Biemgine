#pragma once
#include "bmDrawable.h"
class bmRectangle :
	public bmDrawable
{
public:
	bmRectangle(int x, int y, int width, int height) : bmDrawable(x, y, width, height) { };

	void draw() override;
	void init() override;
	void clear() override;

private:
	GLint shaderProgram;
	GLuint vao;
	GLuint vbo;
	GLuint ebo;

//private:
//	const std::string vertexSource;
//	const std::string fragmentSource;
};

