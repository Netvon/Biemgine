#pragma once

#include "stdafx.h"
#include <string>
#include <glm\glm.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;
using namespace glm;

class bmShaderRef
{
public:

	bmShaderRef(int id) : id(id) {};

	const int& getId() const { return id; }

	void use() const {
		glUseProgram(id);
	};

	void setFloat(const string &name, float value) const {
		glUniform1f(glGetUniformLocation(id, name.c_str()), value);
	}

	void setInt(const string &name, int value) const {
		glUniform1i(glGetUniformLocation(id, name.c_str()), value);
	}

	void setVec2(const string &name, const vec2& value) const {
		glUniform2f(glGetUniformLocation(id, name.c_str()), value.x, value.y);
	}

	void setVec3(const string &name, const vec3& value) const {
		glUniform3f(glGetUniformLocation(id, name.c_str()), value.x, value.y, value.z);
	}

	void setVec4(const string &name, const vec4& value) const {
		glUniform4f(glGetUniformLocation(id, name.c_str()), value.x, value.y, value.z, value.w);
	}
	void setMat4(const string &name, const mat4& value) const {
		glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, value_ptr(value));
	}

protected:
	int id;
};