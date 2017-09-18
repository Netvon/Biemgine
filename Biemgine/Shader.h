#pragma once
class Shader
{
public:
	GLint createProgram(const char * vertex_source, const char * fragmet_source);

private:
	GLint createShader(const char* source, GLenum type);
};

