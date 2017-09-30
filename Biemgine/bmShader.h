#pragma once
#include <string>
#include <glm\glm.hpp>

using namespace std;
using namespace glm;

class bmShader
{
public:

	bmShader() {};
	bmShader(const string& vertex_source, const string& fragmet_source);

	const unsigned int& getId() const { return id; }
	void use() const;

	void setFloat(const string &name, float value) const;
	void setInt(const string &name, int value) const;
	void setVec2(const string &name, const vec2& value) const;
	void setVec3(const string &name, const vec3& value) const;
	void setVec4(const string &name, const vec4& value) const;
	void setMat4(const string &name, const mat4& value) const;

	unsigned int createProgram(const string& vertex_source, const string& fragmet_source);

private:

	unsigned int id;
	unsigned int createShader(const char* source, GLenum type);
};

