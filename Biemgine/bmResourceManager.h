#pragma once
#include <map>
#include <string>
#include "bmShader.h"
using namespace std;

class bmResourceManager
{
public:

	bmShader loadShader(const string & name, const string& vspath, const string& fspath);
	bmShader getShader(const string& name) const;

	void clearShaders();

private:
	map<string, bmShader> shaders;
};

