#include "stdafx.h"
#include "Shader.h"


GLint Shader::createProgram(const char * vertex_source, const char * fragmet_source)
{
	GLint v = createShader(vertex_source, GL_VERTEX_SHADER);
	GLint f = createShader(fragmet_source, GL_FRAGMENT_SHADER);

	GLuint programId = glCreateProgram();
	glAttachShader(programId, v);
	glAttachShader(programId, f);
	glBindFragDataLocation(programId, 0, "color");
	glLinkProgram(programId);

	glDeleteShader(v);
	glDeleteShader(f);

	GLint status = GL_FALSE;
	glGetProgramiv(programId, GL_LINK_STATUS, &status);
	assert(status != GL_FALSE);

	return programId;
}

GLint Shader::createShader(const char * source, GLenum type)
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
