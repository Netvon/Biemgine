#include "stdafx.h"
#include "bmShader.h"
#include <glm/gtc/type_ptr.hpp>

bmShader::bmShader(const string& vertex_source, const string& fragmet_source)
{
	id = createProgram(vertex_source, fragmet_source);
}

void bmShader::use() const
{
	glUseProgram(id);
}

void bmShader::setFloat(const string & name, float value) const
{
	glUniform1f(glGetUniformLocation(id, name.c_str()), value);
}

void bmShader::setInt(const string & name, int value) const
{
	glUniform1i(glGetUniformLocation(id, name.c_str()), value);
}

void bmShader::setVec2(const string & name, const vec2 & value) const
{
	glUniform2f(glGetUniformLocation(id, name.c_str()), value.x, value.y);
}

void bmShader::setVec3(const string & name, const vec3 & value) const
{
	glUniform3f(glGetUniformLocation(id, name.c_str()), value.x, value.y, value.z);
}

void bmShader::setVec4(const string & name, const vec4 & value) const
{
	glUniform4f(glGetUniformLocation(id, name.c_str()), value.x, value.y, value.z, value.w);
}

void bmShader::setMat4(const string & name, const mat4 & value) const
{
	glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, value_ptr(value));
}

unsigned int bmShader::createProgram(const string& vertex_source, const string& fragmet_source)
{
	GLint v = createShader(vertex_source.c_str(), GL_VERTEX_SHADER);
	GLint f = createShader(fragmet_source.c_str(), GL_FRAGMENT_SHADER);

	GLuint programId = glCreateProgram();
	glAttachShader(programId, v);
	glAttachShader(programId, f);
	glLinkProgram(programId);

	glDeleteShader(v);
	glDeleteShader(f);

	GLint status = GL_FALSE;
	glGetProgramiv(programId, GL_LINK_STATUS, &status);
	assert(status != GL_FALSE);

	return programId;
}

unsigned int bmShader::createShader(const char * source, GLenum type)
{
	GLuint res = glCreateShader(type);
	const char* sources[] = { source };
	glShaderSource(res, 1, sources, NULL);
	glCompileShader(res);

	GLint compile_ok = GL_FALSE;
	glGetShaderiv(res, GL_COMPILE_STATUS, &compile_ok);
	if (compile_ok == GL_FALSE)
	{
		fprintf(stderr, "Error compiling shader of type %d!\n", type);
		glDeleteShader(res);
		return 0;
	}

	return res;
}
